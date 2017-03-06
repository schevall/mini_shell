# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schevall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 16:45:19 by schevall          #+#    #+#              #
#    Updated: 2017/03/06 17:05:46 by schevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAG = -Wall -Wextra -Werror
OPTION = -c
SRC_NAME = main.c\
	  builtin_echo.c\
	  builtin_env.c\
	  builtin_set_env.c\

SRC_PATH = srcs/
SRCS = $(addprefix $(SRC_PATH), $(SRCS_NAME))

OBJ_NAME = $(SRC:.c=.o)
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

INC = -I./includes -I/libft/
LIB = -L.libft/ -lft -L.libft/printf/ -lftprintf

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	@make -C ./libft/
	gcc -o $(NAME) $(LIB) $(FLAG) $(OBJ)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p obj
	@gcc -c $(FLAG) $(INC) -o $@ $<

clean:
	@make clean -C ./libft/
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make fclean -C ./libft/
	@/bin/rm -f $(NAME)

re: fclean all