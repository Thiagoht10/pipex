/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:28:08 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/17 01:13:42 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_count
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	*s;
}			t_count;

typedef struct s_file
{
	int	file_in;
	int	file_out;
	pid_t last_pid;
}		t_file;


int	skip_quotes(char *str, char c, int index);
int			count_words(char *str);
void		find_index(int number_word, char *str, int **index);
int			skip_token_chars(char *str, int i);
void		count_len_word(int number_word, char *str, int *index, int **len);
char		*copy_token(char *str, int index, int len);
char		**make_split(int *index, int *len, char *str, int n_word);
void		free_all_arr(char **arr);
char		**ft_split_modified(char *str);
char		*found_path(char **envp);
char		*get_path_executable(char *cmd, char **envp);
char		*resolve_path_exec(char *cmd, char **envp);
int			safe_open_read(const char *path);
int			safe_open_write(const char *path);
void		safe_pipe(int fd[2]);
pid_t		safe_fork(void);
void		die(const char *ctx, int ext);
void		run_pipe(char **argv, char **envp);
void	process_child1(char *argv_cmd, char **envp, int fl_in, int *fd);
void	process_child2(char *argv_cmd, char **envp, int fl_out, int *fd);
int			ft_isdir(char *path);
void		error_path(char **cmd);
int wait_for_children(pid_t last_pid);
void	error_cmd(char **cmd);
#endif