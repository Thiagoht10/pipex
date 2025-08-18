/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:45:34 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/18 00:51:37 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*found_path(char **envp)
{
	t_count	fp;
	int		result;

	fp.i = 0;
	fp.s = "PATH=";
	if (!envp)
		return (NULL);
	while (envp[fp.i])
	{
		result = ft_strncmp(fp.s, envp[fp.i], 5);
		if (result == 0)
			return (envp[fp.i] + 5);
		fp.i++;
	}
	return (NULL);
}

char	*join3(char *dir, char *bar, char *cmd)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(dir, bar);
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, cmd);
	free(temp);
	return (res);
}

char	*get_path_executable(char *cmd, char **envp)
{
	char	**dirs;
	char	*result;
	t_count	exec;

	exec.i = 0;
	exec.s = found_path(envp);
	if (!exec.s)
		return (NULL);
	dirs = ft_split(exec.s, ':');
	if (!dirs || !*dirs)
		return (NULL);
	while (dirs[exec.i])
	{
		result = join3(dirs[exec.i], "/", cmd);
		if (!result)
			return (free_all_arr(dirs), NULL);
		if (access(result, X_OK) == 0)
			return (free_all_arr(dirs), result);
		exec.i++;
		free(result);
	}
	free_all_arr(dirs);
	return (NULL);
}

char	*resolve_path_exec(char *cmd, char **envp)
{
	if (!cmd || !envp || !*envp)
		return (NULL);
	if(cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (ft_isdir(cmd))
			return (NULL);
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (get_path_executable(cmd, envp));
}

int	ft_isdir(char *path)
{
	int		fd;
	char	buf[1];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, buf, 0) < 0 && errno == EISDIR)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
