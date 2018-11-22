# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/30 14:53:21 by ljoly             #+#    #+#              #
#    Updated: 2018/11/22 18:36:23 by ljoly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

SRC = main.c handle_arg.c error.c handle_magic.c handle_64.c sections_64.c \
		symbols.c sort.c free_memory.c data_consistency.c print.c \
		handle_fat32.c swaps.c \

SRC_PATH = ./src/
OBJ_PATH = ./obj/

OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

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
	gcc -fsanitize=address $(FLAGS) -o $(NAME) $(OBJ) -I $(HEADER) -L $(LIBFT) -lft
	@printf "\n$(GREEN)[✓]$(NC)\x1B[32mExecutable $(NAME) ready !\x1B[37m\n"

obj:
	# @make -C $(LIBFT)
	@printf "\n\x1B[38;5;208mCompiling $(NAME)...\n\x1b[37m"
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	gcc $(FLAGS) -I $(LIBFT) -I $(HEADER) -I $(LIBFT_HEADER) -o $@ -c $<
	@printf "\e[38;5;208m▒\e[0m"

clean:
	# @make -C $(LIBFT) clean
	@rm -rf $(OBJ_PATH)
	@printf "$(RED)[-]$(NC)Obj files deleted\n"

fclean: clean
	# @make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@printf "$(RED)[-]$(NC)Executable $(NAME) deleted\n"

re: fclean all

.PHONY: all clean fclean re
