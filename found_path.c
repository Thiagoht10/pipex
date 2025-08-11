/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:45:34 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/11 20:49:24 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *found_path(char **envp)
{
    t_count fp;
    int result;

    fp.i = 0;
    fp.s = "PATH=";
    if(!envp)
        return (NULL);
    while(envp[fp.i])
    {
        result = ft_strncmp(fp.s, envp[fp.i], 5);
        if(result == 0)
            return (envp[fp.i] + 5);
        fp.i++;
    }
    return (NULL);
}

char    *join3(char *dir, char *bar, char *cmd)
{
    char    *temp;
    char    *res;

    temp = ft_strjoin(dir, bar);
    if(!temp)
        return (NULL);
    res = ft_strjoin(temp, cmd);
    free(temp);
    return (res);
}

int is_executable_file(char *cmd, char **envp)
{
    char    **dirs;
    char    *result;
    t_count exec;

    exec.i = 0;
    exec.s = found_path(envp);
    if (!exec.s)
        return(0);
    dirs = ft_split(exec.s, ':');
    if(!dirs || !dirs[0])
        return (-1);
    while(dirs[exec.i])
    {
        result = join3(dirs[exec.i], "/", cmd);
        if(!result)
            return (free_all_arr(dirs), -1);
        if (access(result, X_OK) == 0)
            return (free_all_arr(dirs), free(result), 1);
        exec.i++;
        free(result);
    }
    free_all_arr(dirs);
    return (0);
}
