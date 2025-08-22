/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:44:38 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/22 18:49:23 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_before_dup(char **cmd, char *path, int fd)
{
	if (fd == -1)
	{
		free_all_arr(cmd);
		free(path);
	}
}

int	safe_open_write_child(const char *path, int fd1, int fd2)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		close_fd(fd1, fd2, -1, -1);
		perror(path);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	check_open(char **argv)
{
	int	in;
	int	out;

	in = open(argv[1], O_RDONLY);
	if (in < 0)
		perror(argv[1]);
	out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out < 0)
	{
		perror(argv[4]);
		close_fd(out, in, -1, -1);
		exit(EXIT_FAILURE);
	}
	close_fd(in, out, -1, -1);
}
