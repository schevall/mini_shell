# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schevall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 16:45:19 by schevall          #+#    #+#              #
#    Updated: 2017/05/18 11:06:00 by schevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
SRC_NAME = main.c\
		   path_manager.c\
		   path_maker.c\
	  builtin_echo.c\
	  builtin_env.c\
	  builtin_set_env.c\
	  builtin_unset_env.c\
	  builtin_cd.c\
	  builtin_exit.c\
	  builtin_pwd.c\
	  bonus_get_prompt.c\
	  bonus_sigign_prompt.c\
	  minishell_errors.c\

SRC_PATH = srcs/
SRCS = $(addprefix $(SRC_PATH), $(SRCS_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

INC = -I includes/ -I libft/
LIB = -L ./libft/ -lft -L ./libft/printf/ -lftprintf

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	@make -C ./libft/
	gcc $(FLAGS) $(INC) $(LIB) -o $(NAME) $(OBJ)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p obj
	@gcc -c -g $(FLAG) $(INC) -o $@ $<

clean:
	@make clean -C ./libft/
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make fclean -C ./libft/
	@/bin/rm -f $(NAME)

re: fclean all
