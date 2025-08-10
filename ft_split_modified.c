/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_modified.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:53:58 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/10 18:45:08 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all_arr(char **arr)
{
	int	a;

	a = 0;
	while (arr[a])
	{
		if (arr[a])
			free(arr[a]);
		a++;
	}
	free(arr);
}

char    *copy_token(char *str, int index, int len, int number_word)
{
    char    *s;
    t_count cpy;

    cpy.i = 0;
    cpy.j = 0;
    s = malloc((len + 1) * sizeof(char));
    if(!str)
        return (NULL);
    cpy.start = index - (len - 1);
    cpy.end = index;
    if((str[cpy.end] == 34 || str[cpy.end] == 39))
    {
        cpy.end--;
        cpy.start = index - len;
    }
    while(cpy.start <= cpy.end)
    {
        s[cpy.j] = str[cpy.start];
        cpy.start++;
        cpy.j++;
    }
    s[cpy.j] = '\0';
    return (s);
}

char **make_split(int *index, int *len, char *str, int n_word)
{
    char    **arr;
    t_count count;

    count.j = 0;
    arr = malloc((n_word + 1) * sizeof(char *));
    if(!arr)
        return (NULL);
    while(count.j < n_word)
    {
        arr[count.j] = copy_token(str, index[count.j], len[count.j], n_word);
        count.j++;
    }
    return (arr);
}

/* int ft_split_modified(char *str)
{
    int *index;
    int number_word;
    int *len_word;
    char **arr;

    number_word = count_words(str);
    find_index(number_word, str, &index);
    count_len_word(number_word, str, index, &len_word);
    arr = make_split(index, len_word, str, number_word);

} */
