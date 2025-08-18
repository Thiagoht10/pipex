/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:53:25 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/18 01:25:23 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_path(char **cmd)
{
	if (cmd)
	{
		if (ft_isdir(cmd[0]))
		{
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": Is a directory\n", 17);
			free_all_arr(cmd);
			exit(126);
		}
		else if (ft_strchr(cmd[0], '/'))
		{
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": No such file or directory\n", 28);
			free_all_arr(cmd);
			exit(127);
		}
		else if (cmd[0][0] == '\0')
			aux_error_path(cmd);
	}
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	free_all_arr(cmd);
	exit(127);
}

void	error_cmd(char **cmd)
{
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
	{
		write(2, ": command not found\n", 20);
		exit(127);
	}
}

void	close_fd(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (fd4 != -1)
		close(fd4);
}

void	aux_error_path(char **cmd)
{
	write(2, "'': command not found\n", 22);
	free_all_arr(cmd);
	exit(127);
}
