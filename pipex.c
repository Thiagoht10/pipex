/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:09:52 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/09 20:44:16 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
    int i = 0;
    int *index;
    int number_word;

    number_word = count_words(argv[1]);
    find_index(number_word, argv[1], &index);
    printf("word: %d\n", number_word);
    while(i < number_word)
        printf("index(%d): %d\n", i, index[i++]);
    free(index);
    return (0);
}