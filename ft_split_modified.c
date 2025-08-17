/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_modified.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:53:58 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/16 22:32:42 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all_arr(char **arr)
{
	int	a;

	a = 0;
	if(!arr || !*arr)
		return ;
	while (arr[a])
	{
		if (arr[a])
			free(arr[a]);
		a++;
	}
	free(arr);
}
int	count_words(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (str[i] != '\0')
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

char	*copy_token(char *str, int index, int len)
{
	char	*token;
	int		end_exclusive;
	int		token_length;
	int		start;
	int		i;

	end_exclusive = index;  
	token_length = len;
	token = (char *)malloc((token_length + 1) * sizeof(char));
	if (!token)
		return (NULL);
	start = end_exclusive - token_length;
	i = 0;
	while (i < token_length)
	{
		token[i] = str[start + i];
		i++;
	}
	token[i] = '\0';
	return (token);
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

	index = NULL;
	len_word = NULL;
	number_word = count_words(str);
	find_index(number_word, str, &index);
	if(!index)
		return(free(index), NULL);
	count_len_word(number_word, str, index, &len_word);
	if(!len_word)
		return (free(len_word), NULL);
	arr = make_split(index, len_word, str, number_word);
	if(!arr || !*arr)
	{
		free_all_arr(arr);
		free(index);
		free(len_word);
		return (NULL);
	}
	free(index);
	free(len_word);
	return (arr);
}
