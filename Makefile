# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/30 14:53:21 by ljoly             #+#    #+#              #
#    Updated: 2018/11/05 15:39:48 by ljoly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

SRC = main.c error.c

SRC_PATH = ./src/

SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(SRCS:.c=.o)


FLAGS = -Wall -Werror -Wextra
LIBFT = ./libft/
LIBFT_HEADER = ./libft/includes
HEADER = ./includes/

RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

.SILENT:

all: $(NAME)

$(NAME): obj $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) -I $(HEADER) -L $(LIBFT) -lft
	@printf "\n$(GREEN)[✓]$(NC)\x1B[32mExecutable $(NAME) ready !\x1B[37m\n"

obj:
	# @make -C $(LIBFT)
	@printf "\n\x1B[38;5;208mCompiling $(NAME)...\n\x1b[37m"

%.o: %.c
	gcc $(FLAGS) -I $(LIBFT) -I $(HEADER) -I $(LIBFT_HEADER) -o $@ -c $<
	@printf "\e[38;5;208m▒\e[0m"

clean:
	# @make -C $(LIBFT) clean
	@rm -rf $(OBJ)
	@printf "$(RED)[-]$(NC)Obj files deleted\n"

fclean: clean
	# @make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@printf "$(RED)[-]$(NC)Executable $(NAME) deleted\n"

re: fclean all

.PHONY: all clean fclean re
