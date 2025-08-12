/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:09:52 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/12 05:14:04 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**arr;
	char	*path;
	int		i;

	if (argc < 2)
		return (0);
	arr = ft_split_modified(argv[1]);
	if (!arr)
		return (-1);
	i = 0;
	while (arr[i])
	{
		printf("\ntoken(%d): %s\n", i, arr[i]);
		i++;
	}
	path = resolve_path_exec(arr[0], envp);
	printf("\nPATH_found: %s\n", found_path(envp));
	printf("\nPATH executable: %s\n", path);
	free(path);
	free_all_arr(arr);
	return (0);
}
