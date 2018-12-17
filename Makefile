# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/30 14:53:21 by ljoly             #+#    #+#              #
#    Updated: 2018/12/17 19:37:44 by ljoly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NM = ft_nm
NAME_OTOOL = ft_otool

SRC_NM = main.c handle_arg.c error.c handle_magic.c handle_64.c get_sections_64.c \
		get_symbols.c sort.c free_memory.c data_consistency_64.c print.c \
		handle_fat_32.c swaps.c check_access.c data_consistency_32.c \
		handle_fat_64.c handle_arch.c handle_32.c get_sections_32.c cpu.c

SRC_OTOOL = main.c handle_arg.c error.c handle_magic.c handle_64.c get_sections_64.c \
		free_memory.c data_consistency_64.c print.c handle_fat_32.c swaps.c \
		check_access.c data_consistency_32.c handle_fat_64.c \
		handle_arch.c handle_32.c get_sections_32.c cpu.c

SRC_NM_PATH = ./src_nm/
SRC_OTOOL_PATH = ./src_otool/
OBJ_NM_PATH = ./obj_nm/
OBJ_OTOOL_PATH = ./obj_otool/

OBJ_NM = $(addprefix $(OBJ_NM_PATH), $(SRC_NM:.c=.o))
OBJ_OTOOL = $(addprefix $(OBJ_OTOOL_PATH), $(SRC_OTOOL:.c=.o))

FLAGS = -Wall -Werror -Wextra
LIBFT = ./libft/
LIBFT_HEADER = ./libft/includes
HEADER = ./includes/

RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

.SILENT:

all: $(NAME_NM) $(NAME_OTOOL)

$(NAME_NM): obj_nm $(OBJ_NM)
	gcc $(FLAGS) -o $(NAME_NM) $(OBJ_NM) -I $(HEADER) -L $(LIBFT) -lft
	@printf "\n$(GREEN)[✓]$(NC)\x1B[32mExecutable $(NAME_NM) ready !\x1B[37m\n"

obj_nm:
	# @make -C $(LIBFT)
	@printf "\n\x1B[38;5;208mCompiling $(NAME_NM)...\n\x1b[37m"
	@mkdir -p $(OBJ_NM_PATH)

$(NAME_OTOOL): obj_otool $(OBJ_OTOOL)
	gcc $(FLAGS) -o $(NAME_OTOOL) $(OBJ_OTOOL) -I $(HEADER) -L $(LIBFT) -lft
	@printf "\n$(GREEN)[✓]$(NC)\x1B[32mExecutable $(NAME_OTOOL) ready !\x1B[37m\n"

obj_otool:
	@printf "\n\x1B[38;5;208mCompiling $(NAME_OTOOL)...\n\x1b[37m"
	@mkdir -p $(OBJ_OTOOL_PATH)

$(OBJ_NM_PATH)%.o: $(SRC_NM_PATH)%.c
	gcc $(FLAGS) -I $(LIBFT) -I $(HEADER) -I $(LIBFT_HEADER) -o $@ -c $<
	@printf "\e[38;5;208m▒\e[0m"

$(OBJ_OTOOL_PATH)%.o: $(SRC_OTOOL_PATH)%.c
	gcc $(FLAGS) -I $(LIBFT) -I $(HEADER) -I $(LIBFT_HEADER) -o $@ -c $<
	@printf "\e[38;5;208m▒\e[0m"

clean:
	# @make -C $(LIBFT) clean
	@rm -rf $(OBJ_NM_PATH)
	@rm -rf $(OBJ_OTOOL_PATH)
	@printf "$(RED)[-]$(NC)Obj files deleted\n"

fclean: clean
	# @make -C $(LIBFT) fclean
	@rm -f $(NAME_NM)
	@rm -f $(NAME_OTOOL)
	@printf "$(RED)[-]$(NC)Executable $(NAME_NM) deleted\n"
	@printf "$(RED)[-]$(NC)Executable $(NAME_OTOOL) deleted\n"

re: fclean all

.PHONY: all clean fclean re
