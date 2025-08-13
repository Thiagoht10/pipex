/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:27:48 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/13 05:17:07 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	skip_quotes(char *str, char c, int index)
{
	int	i;

	i = index + 1;
	while (str[i] != '\0')
	{
		if (str[i] == c && (str[i + 1] == 32 || str[i + 1] == '\0'))
			return (i);
		i++;
	}
	return (index);
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

void	find_index(int number_word, char *str, int **index)
{
	int	k;
	int	i;
	int	j;

	i = 0;
	j = 0;
	*index = (int *)malloc((number_word + 1) * sizeof(int));
	if (!index)
		return ;
	while (str[i] == 32)
		i++;
	while (str[i] != '\0' && j < number_word)
	{
		k = skip_token_chars(str, i);
		(*index)[j++] = k - 1;
		i = k;
		while (str[i] == 32)
			i++;
	}
	(*index)[j] = 0;
}

int	skip_token_chars(char *str, int i)
{
	int	close;

	while (str[i] != '\0' && str[i] != 32)
	{
		if (str[i] == 34 || str[i] == 39)
		{
			close = skip_quotes(str, str[i], i);
			if (close == i)
			{
				while (str[i] != '\0' && str[i] != 32)
					i++;
				break ;
			}
			i = close + 1;
		}
		else
			i++;
	}
	return (i);
}

void	count_len_word(int number_word, char *str, int *index, int **len)
{
	t_count	count;

	count.i = 0;
	count.j = 0;
	*len = (int *)malloc((number_word + 1) * sizeof(int));
	if (!len)
		return ;
	while (str[count.i] == 32)
		count.i++;
	while (count.j < number_word)
	{
		count.start = count.i;
		count.end = index[count.j];
		if ((str[count.start] == 34 || str[count.start] == 39)
			&& (str[count.end] == str[count.start]))
		{
			count.end--;
			count.start++;
		}
		(*len)[count.j] = count.end - count.start + 1;
		count.i = index[count.j] + 1;
		while (str[count.i] != '\0' && str[count.i] == 32)
			count.i++;
		count.j++;
	}
}
