/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:09:52 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/18 01:26:07 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	/* char **cmd;
	char *path;

	cmd = ft_split_modified(argv[3]);
	path = resolve_path_exec(cmd[0], envp);
	printf("\nCMD: (%s) -- PATH: %s\n", cmd[0], path); */
	if (argc != 5)
		exit(EXIT_FAILURE);
	run_pipe(argv, envp);
	return (0);
}
