/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_modified.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:27:48 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/09 20:43:10 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int skip_quotes(char *str, char c, int index)
{
    int i;
    
    i = index + 1;
    while (str[i] != '\0')
    {
        if (str[i] == c && (str[i + 1] == 32 || str[i + 1] == '\0'))
            return i;
        i++;
    }
    return (index);
}

int count_words(char *str)
{
    int i;
    int count;
    char    c;

    i = 0;
    count = 0;
    while(str[i] != '\0')
    {
        if ((i == 0 || str[i - 1] == 32) && str[i] != 32)
        {
            if (str[i] == 34 || str[i] == 39)
            {
                c = str[i];
                i = skip_quotes(str, c, i);
            }
            count++;
        }
        i++;
    }
    return (count);
}

void find_index(int number_word, char *str, int **index)
{
    int i;
    int j;
    char    c;

    i = 0;
    j = 0;
    *index = (int *)malloc(number_word * sizeof(int));
    if(!*index)
        return ;
    while(str[i] == 32)
        i++;
    while(str[i] != '\0' && j < number_word)
    {
        if (str[i] == 32)
        {
            (*index)[j] = i - 1;
            while(str[i] == 32)
                i++;
            j++;
        }
        else if (str[i + 1] == '\0')
            (*index)[j] = i;
        if (str[i] == 34 || str[i] == 39)
        {
            c = str[i];
            i = skip_quotes(str, c, i);
            (*index)[j] = i;
        }
        i++;
    }
}
