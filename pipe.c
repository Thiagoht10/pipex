/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:48:15 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/18 19:29:10 by thde-sou         ###   ########.fr       */
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
	safe_pipe(fd);
	pid1 = safe_fork();
	if (pid1 == 0)
		process_child1(argv[2], envp, fl.file_in, fd);
	close(fl.file_in);
	fl.file_out = safe_open_write(argv[4]);
	write(2, "aqui\n", 5);
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
	{
		close_fd(fl_in, fd[1], fd[0], -1);
		error_cmd(cmd);
	}
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
	{
		close_fd(fl_in, fd[1], fd[0], -1);
		error_path(cmd);
	}
	make_dup2(fl_in, fd[1], fd[0], -1);
	close_fd(fd[0], fd[1], fl_in, -1);
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
	{
		close_fd(fl_out, fd[1], fd[0], -1);
		error_cmd(cmd);
	}
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
	{
		close_fd(fl_out, fd[1], fd[0], -1);
		error_path(cmd);
	}
	make_dup2(fd[0], fl_out, fd[1], -1);
	close_fd(fd[0], fd[1], fl_out, -1);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	exit(127);
}

int	wait_for_children(pid_t last_pid)
{
	int		status;
	int		exit_code;
	pid_t	wpid;

	exit_code = 0;
	wpid = 1;
	while (wpid > 0)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
	}
	return (exit_code);
}

void	make_dup2(int fd_in, int fd_out, int fd3, int fd4)
{
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		close_fd(fd_in, fd_out, fd3, fd4);
		die("pipe_in", 1);
	}
	if (dup2(fd_out, STDOUT_FILENO) < 0)
	{
		close_fd(fd_in, fd_out, fd3, fd4);
		die("pipe_out", 1);
	}
}
