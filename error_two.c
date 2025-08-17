/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:53:25 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/17 01:04:09 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_path(char **cmd)
{	
	if(cmd)
	{
		if (ft_isdir(cmd[0]))
		{
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": Is a directory\n", 17);
			free_all_arr(cmd);
			exit(126);
		}
		else if(ft_strchr(cmd[0], '/'))
		{
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": No such file or directory\n", 28);
			free_all_arr(cmd);
			exit(127);	
		}
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
    	write(2, "pipex: : command not found\n", 27);
    	free_all_arr(cmd);
    	exit(127);
	}
}
