/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:53:25 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/13 00:19:52 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_path(char **cmd)
{
	if (ft_isdir(cmd[0]))
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": Is a directory\n", 17);
		free_all_arr(cmd);
		exit(126);
	}
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	free_all_arr(cmd);
	exit(127);
}
