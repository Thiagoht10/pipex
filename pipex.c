/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:09:52 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/10 19:25:09 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
    char **arr;
    int i;

    i = 0;
    arr = ft_split_modified(argv[1]);
    if(!arr)
        return (-1);
    while(**arr)
    {
        printf("\ntoken: %s\n", arr[i]);
        i++;
    }
    free_all_arr(arr);
    return (0);
}