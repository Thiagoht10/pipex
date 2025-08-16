/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:48:15 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/16 06:04:22 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void    run_pipe(int argc, char **argv, char **envp)
{
    t_fd    f;
    t_count p;

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
    if (f.pid == 0)
        process_child_end(argc, argv, envp, f.fd);
    if (f.fd[0] != -1)
        close(f.fd[0]);
    while (wait(NULL) > 0)
        (void)0;
}


void	process_child_start(char **argv, char **envp, int *temp_fd)
{
	char	**cmd;
	char	*path;
	int		file_in;

	cmd = ft_split_modified(argv[2]);
	if (!cmd || !*cmd)
		die("parse_cmd1", 127);
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
		error_path(cmd);
	file_in = safe_open_read(argv[1]);
	if (dup2(file_in, STDIN_FILENO) < 0)
		die("file_in", 1);
	if (dup2(temp_fd[1], STDOUT_FILENO) < 0)
		die("pipe_write", 1);
	close(file_in);
	close(temp_fd[0]);
	close(temp_fd[1]);
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
		die("parse_cmd_middle", 127);
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
		error_path(cmd);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		die("pipe_read", 1);
	if (dup2(temp_fd[1], STDOUT_FILENO) < 0)
		die("pipe_write", 1);
	close(fd[0]);
	close(temp_fd[0]);
	close(temp_fd[1]);
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

	cmd = ft_split_modified(argv[argc - 2]);
	if (!cmd || !*cmd)
		die("parse_cmd2", 127);
	path = resolve_path_exec(cmd[0], envp);
	if (!path)
		error_path(cmd);
	file_out = safe_open_write(argv[argc - 1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		die("pipe_read", 1);
	if (dup2(file_out, STDOUT_FILENO) < 0)
		die("file_out", 1);
	close(fd[0]);
	close(file_out);
	execve(path, cmd, envp);
	perror(cmd[0]);
	free_all_arr(cmd);
	free(path);
	exit(127);
}
