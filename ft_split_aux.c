/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:27:48 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/18 15:25:39 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	skip_quotes(char *str, char c, int index)
{
	int	i;

	i = index + 1;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (index);
}

void	find_index(int number_word, char *str, int **index)
{
	int	k;
	int	i;
	int	j;

	i = 0;
	j = 0;
	*index = (int *)malloc((number_word + 1) * sizeof(int));
	if (!index || !*index)
		return ;
	while (str[i] == 32)
		i++;
	while (str[i] != '\0' && j < number_word)
	{
		k = skip_token_chars(str, i);
		(*index)[j++] = k;
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

static void	update_index(char *str, int start, int *end, int *len)
{
	int	end_inclusive;

	end_inclusive = *end - 1;
	if ((str[start] == 34 || str[start] == 39)
		&& end_inclusive > start && str[end_inclusive] == str[start])
	{
		if (end_inclusive > start + 1)
			*len = end_inclusive - start - 1;
		else
			*len = 0;
		*end = end_inclusive;
	}
	else
	{
		if (*end > start)
			*len = *end - start;
		else
			*len = 0;
	}
}

void	count_len_word(int number_word, char *str, int *index, int **len)
{
	int	i;
	int	j;
	int	start;
	int	end_exclusive;

	i = 0;
	j = 0;
	*len = (int *)malloc((number_word + 1) * sizeof(int));
	if (!*len)
		return ;
	while (str[i] && str[i] == 32)
		i++;
	while (j < number_word)
	{
		start = i;
		end_exclusive = index[j];
		update_index(str, start, &index[j], &(*len)[j]);
		i = end_exclusive;
		while (str[i] && str[i] == 32)
			i++;
		j++;
	}
}
