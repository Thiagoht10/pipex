/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:48:15 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/18 15:35:46 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_fds(t_fd *f)
{
	f->fd[0] = -1;
	f->fd[1] = -1;
	f->temp_fd[0] = -1;
	f->temp_fd[1] = -1;
}

void	init_count(t_count *p, int argc)
{
	p->i = 0;
	p->n = argc - 4;
}

void	parent_step(t_fd *f)
{
	close(f->temp_fd[1]);
	if (f->fd[0] != -1)
		close(f->fd[0]);
	f->fd[0] = f->temp_fd[0];
	f->temp_fd[0] = -1;
	f->temp_fd[1] = -1;
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
