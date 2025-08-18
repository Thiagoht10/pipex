/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:48:15 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/18 19:33:10 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	run_pipe_bonus(int argc, char **argv, char **envp)
{
	t_fd	f;
	t_count	p;
	pid_t	last_pid;

	init_fds(&f);
	init_count(&p, argc);
	while (p.i < p.n)
	{
		safe_pipe(f.temp_fd);
		f.pid = safe_fork();
		if (f.pid == 0 && p.i == 0)
			process_child_start(argv, envp, f.temp_fd);
		else if (f.pid == 0)
			process_child_middle(argv[2 + p.i], envp, f.temp_fd, f.fd);
		parent_step(&f);
		p.i++;
	}
	f.pid = safe_fork();
	last_pid = f.pid;
	if (f.pid == 0)
		process_child_end(argc, argv, envp, f.fd);
	if (f.fd[0] != -1)
		close(f.fd[0]);
	exit(wait_for_children(last_pid));
}

void	process_child_start(char **argv, char **envp, int *temp_fd)
{
	char	**cmd;
	char	*path;
	int		file_in;

	cmd = ft_split_modified(argv[2]);
	if (!cmd || !*cmd)
	{
		close_fd(temp_fd[0], temp_fd[1], -1, -1);
		error_cmd(cmd);
	}
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
	{
		close_fd(temp_fd[0], temp_fd[1], -1, -1);
		error_path(cmd);
	}
	file_in = safe_open_read(argv[1]);
	make_dup2(file_in, temp_fd[1], temp_fd[0], -1);
	close_fd(temp_fd[0], temp_fd[1], file_in, -1);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	exit(127);
}

void	process_child_middle(char *arg, char **envp, int *temp_fd, int *fd)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_modified(arg);
	if (!cmd || !*cmd)
	{
		close_fd(fd[0], temp_fd[0], temp_fd[1], -1);
		error_cmd(cmd);
	}
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
	{
		close_fd(fd[0], temp_fd[0], temp_fd[1], -1);
		error_path(cmd);
	}
	make_dup2(fd[0], temp_fd[1], temp_fd[0], -1);
	close_fd(temp_fd[0], temp_fd[1], fd[0], -1);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	exit(127);
}

void	process_child_end(int argc, char **argv, char **envp, int *fd)
{
	char	**cmd;
	char	*path;
	int		file_out;

	file_out = safe_open_write(argv[argc - 1]);
	cmd = ft_split_modified(argv[argc - 2]);
	if (!cmd || !*cmd)
	{
		close_fd(fd[0], -1, -1, -1);
		error_cmd(cmd);
	}
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
	{
		close_fd(fd[0], -1, -1, -1);
		error_path(cmd);
	}
	make_dup2(fd[0], file_out, -1, -1);
	close_fd(fd[0], file_out, -1, -1);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	exit(127);
}
