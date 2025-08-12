# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 18:08:12 by thde-sou          #+#    #+#              #
#    Updated: 2025/08/12 20:10:13 by thde-sou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = pipex.a

EXEC = pipex

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LEAK_MEMORY = valgrind -s --leak-check=full

ARGS = $(filter-out $@,$(MAKECMDGOALS))

SRC = found_path.c ft_split_aux.c ft_split_modified.c pipex.c pipe.c error.c
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ) $(LIBFT)
	ar rcsT $(NAME) $(OBJ) $(LIBFT)
	$(CC) $(NAME) -o $(EXEC)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

leak: $(NAME)
	$(LEAK_MEMORY) ./$(EXEC) $(ARGS)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(EXEC)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re leak
