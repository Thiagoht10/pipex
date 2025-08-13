/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:48:15 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/13 04:38:49 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_pipe(int argc, char **argv, char **envp)
{
	int		file_in;
	int		file_out;
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	file_in = safe_open_read(argv[1]);
	file_out = safe_open_write(argv[argc - 1]);
	safe_pipe(fd);
	pid1 = safe_fork();
	if (pid1 == 0)
		process_child1(argv[2], envp, file_in, fd);
	pid2 = safe_fork();
	if (pid2 == 0)
		process_child2(argv[3], envp, file_out, fd);
	close(fd[0]);
	close(fd[1]);
	close(file_in);
	close(file_out);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	process_child1(char *argv_cmd, char **envp, int file_in, int *fd)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_modified(argv_cmd);
	if (!cmd || !*cmd)
		die("parse_cmd1", 127);
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
		error_path(cmd);
	if (dup2(file_in, STDIN_FILENO) < 0)
		die("file_in", 1);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		die("pipe_write", 1);
	close(fd[0]);
	close(fd[1]);
	close(file_in);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	exit(127);
}

void	process_child2(char *argv_cmd, char **envp, int file_out, int *fd)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_modified(argv_cmd);
	if (!cmd || !*cmd)
		die("parse_cmd2", 127);
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
		error_path(cmd);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		die("pipe_read", 1);
	if (dup2(file_out, STDOUT_FILENO) < 0)
		die("file_out", 1);
	close(fd[0]);
	close(fd[1]);
	close(file_out);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	exit(127);
}
