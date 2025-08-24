/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:55:11 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/24 03:10:26 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	safe_open_write_child(const char *path, int fd1, int fd2)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		close_fd(fd1, fd2, -1, -1);
		perror(path);
		exit(1);
	}
	return (fd);
}

void	safe_pipe(int fd[2])
{
	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
}

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

void	die(const char *ctx, int ext)
{
	if (!ctx)
		exit(EXIT_FAILURE);
	perror(ctx);
	exit(ext);
}
