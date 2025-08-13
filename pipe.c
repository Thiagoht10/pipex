/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:48:15 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/13 22:55:58 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_file	*creat_struct(void)
{
	t_file *stack;

	stack = malloc(sizeof(t_file));
	if(!stack)
		return (NULL);
	return (stack);
}

void	run_pipe(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	t_file	*fl;

	fl = creat_struct();
	if (!fl)
		free(fl);
	fl->file_in = safe_open_read(argv[1]);
	fl->file_out = safe_open_write(argv[4]);
	safe_pipe(fd);
	pid1 = safe_fork();
	if (pid1 == 0)
		process_child1(argv[2], envp, fl, fd);
	pid2 = safe_fork();
	if (pid2 == 0)
		process_child2(argv[3], envp, fl, fd);
	close(fl->file_in);
	close(fl->file_out);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free(fl);
}

void	process_child1(char *argv_cmd, char **envp, t_file *fl, int *fd)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_modified(argv_cmd);
	if (!cmd || !*cmd)
		die("parse_cmd1", 127);
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
		error_path(cmd);
	if (dup2(fl->file_in, STDIN_FILENO) < 0)
		die("file_in", 1);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		die("pipe_write", 1);
	close(fd[0]);
	close(fd[1]);
	close(fl->file_in);
	close(fl->file_out);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	free(fl);
	exit(127);
}

void	process_child2(char *argv_cmd, char **envp, t_file *fl, int *fd)
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
	if (dup2(fl->file_out, STDOUT_FILENO) < 0)
		die("file_out", 1);
	close(fd[0]);
	close(fd[1]);
	close(fl->file_in);
	close(fl->file_out);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	free(fl);
	exit(127);
}
