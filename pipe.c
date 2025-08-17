/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:48:15 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/17 01:13:50 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_pipe(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	t_file	fl;

	fl.file_in = safe_open_read(argv[1]);
	fl.file_out = safe_open_write(argv[4]);
	safe_pipe(fd);
	pid1 = safe_fork();
	if (pid1 == 0)
		process_child1(argv[2], envp, fl.file_in, fd);
	pid2 = safe_fork();
	if (pid2 == 0)
		process_child2(argv[3], envp, fl.file_out, fd);
	fl.last_pid = pid2;
	close(fl.file_in);
	close(fl.file_out);
	close(fd[0]);
	close(fd[1]);
	exit(wait_for_children(fl.last_pid));
}

void	process_child1(char *argv_cmd, char **envp, int fl_in, int *fd)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_modified(argv_cmd);
	if (!cmd || !*cmd)
		die(NULL, 127);
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
		error_path(cmd);
	if (dup2(fl_in, STDIN_FILENO) < 0)
		die("file_in", 1);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		die("pipe_write", 1);
	close(fd[0]);
	close(fd[1]);
	close(fl_in);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	exit(127);
}

void	process_child2(char *argv_cmd, char **envp, int fl_out, int *fd)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_modified(argv_cmd);
	if (!cmd || !*cmd)
		error_cmd(cmd);
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
		error_path(cmd);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		die("pipe_read", 1);
	if (dup2(fl_out, STDOUT_FILENO) < 0)
		die("file_out", 1);
	close(fd[0]);
	close(fd[1]);
	close(fl_out);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	exit(127);
}

int wait_for_children(pid_t last_pid)
{
    int status;
    int exit_code;
    pid_t wpid;

	exit_code = 0;
    while ((wpid = waitpid(-1, &status, 0)) > 0)
    {
        if (wpid == last_pid)
        {
            if (WIFEXITED(status))
                exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                exit_code = 128 + WTERMSIG(status);
        }
    }
    return exit_code;
}
