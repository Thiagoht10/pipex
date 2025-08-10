/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:28:08 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/10 18:35:59 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include "libft/libft.h"

typedef struct s_count
{
    int i;
    int j;
    int start;
    int end;
    char    *s;
}               t_count;


int count_words(char *str);
int count_words(char *str);
void find_index(int number_word, char *str, int **index);
int skip_token_chars(char *str, int i);
void    count_len_word(int number_word, char *str, int *index, int **len);
char    *copy_token(char *str, int index, int len, int number_word);
char **make_split(int *index, int *len, char *str, int n_word);
void	free_all_arr(char **arr);
#endif