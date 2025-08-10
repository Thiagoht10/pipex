/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:09:52 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/10 17:27:12 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
    int i = 0;
    int *index;
    int number_word;
    int *len_word;
    char **arr;

    number_word = count_words(argv[1]);
    find_index(number_word, argv[1], &index);
    count_len_word(number_word, argv[1], index, &len_word);
    arr = make_split(index, len_word, argv[1], number_word);
    printf("word: %d\n", number_word);
    while(i < number_word)
    {
        printf("index(%d): %d | len(%d): %d | token: %s\n", i, index[i], i, len_word[i], arr[i]);
        i++;
    }
    free(index);
    free(len_word);
    return (0);
}