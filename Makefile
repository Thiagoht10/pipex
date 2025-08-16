# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 18:08:12 by thde-sou          #+#    #+#              #
#    Updated: 2025/08/16 06:09:36 by thde-sou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = pipex.a

EXEC = pipex

MARKER = .bonus_created

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_COMMON = found_path.c ft_split_aux.c ft_split_modified.c error.c error_two.c

SRC = pipex.c pipe.c $(SRC_COMMON)

SRC_BONUS = pipex_bonus.c pipe_bonus.c pipe_bonus_two.c $(SRC_COMMON)

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ) $(LIBFT)
	ar rcsT $(NAME) $(OBJ) $(LIBFT)
	$(CC) $(NAME) -o $(EXEC)

bonus: $(MARKER) $(LIBFT)

$(MARKER): $(OBJ_BONUS) $(LIBFT)
	rm -rf $(NAME)
	ar rcsT $(NAME) $(OBJ_BONUS) $(LIBFT)
	$(CC) $(NAME) -o $(EXEC)
	touch $(MARKER)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS) 
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(EXEC) $(MARKER)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re leak
