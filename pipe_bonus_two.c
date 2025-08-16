/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:48:15 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/16 05:56:07 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void init_fds(t_fd *f)
{
    f->fd[0] = -1;
    f->fd[1] = -1;
    f->temp_fd[0] = -1;
    f->temp_fd[1] = -1;
}

void init_count(t_count *p, int argc)
{
    p->i = 0;
    p->n = argc - 4;
}

void parent_step(t_fd *f)
{
    close(f->temp_fd[1]);
    if (f->fd[0] != -1)
        close(f->fd[0]);
    f->fd[0] = f->temp_fd[0];
}

