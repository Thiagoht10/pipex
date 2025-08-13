/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_modified.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:53:58 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/13 05:49:28 by thde-sou         ###   ########.fr       */
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

char	*copy_token(char *str, int index, int len)
{
	char	*s;
	t_count	cpy;

	cpy.i = 0;
	cpy.j = 0;
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	cpy.start = index - (len - 1);
	cpy.end = index;
	if ((str[cpy.end] == 34 || str[cpy.end] == 39))
	{
		cpy.end--;
		cpy.start = index - len;
	}
	while (cpy.start <= cpy.end)
	{
		s[cpy.j] = str[cpy.start];
		cpy.start++;
		cpy.j++;
	}
	s[cpy.j] = '\0';
	return (s);
}

char	**make_split(int *index, int *len, char *str, int n_word)
{
	char	**arr;
	t_count	count;

	count.j = 0;
	arr = malloc((n_word + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (count.j < n_word)
	{
		arr[count.j] = copy_token(str, index[count.j], len[count.j]);
		if(!arr[count.j])
		{
			free_all_arr(arr);
			return (NULL);
		}
		count.j++;
	}
	arr[count.j] = NULL;
	return (arr);
}

char	**ft_split_modified(char *str)
{
	int		*index;
	int		number_word;
	int		*len_word;
	char	**arr;

	number_word = count_words(str);
	find_index(number_word, str, &index);
	if(!index)
		return(NULL);
	count_len_word(number_word, str, index, &len_word);
	if(!len_word)
		return (NULL);
	arr = make_split(index, len_word, str, number_word);
	if(!arr)
		return (NULL);
	free(index);
	free(len_word);
	return (arr);
}
