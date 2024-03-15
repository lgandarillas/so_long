# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgandari <lgandari@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 15:52:22 by lgandari          #+#    #+#              #
#    Updated: 2024/03/15 15:52:27 by lgandari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=	\033[0;31m
GREEN	=	\033[0;32m
NC		=	\033[0m 

NAME	=	so_long

SRC_DIR	= src/
OBJ_DIR	= obj/
INC_DIR	= inc/

SRC		= $(addprefix $(SRC_DIR), \
		  check_map.c	check_path.c	error.c	game.c \
		  main.c	moves.c	save_map.c)

OBJ		= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

LIBFT		= libft_v2/libft_v2.a
LIBFT_PATH	= libft_v2/

MLX			= mlx/libmlx.a
MLX_PATH	= mlx/

CC			= gcc
RM			= rm -f
C_FLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	= -framework OpenGL -framework AppKit
INCS		= -I$(INC_DIR) -I.

TOTAL_FILES		:= $(words $(SRC))
CURRENT_FILES	:= 0

define progress_bar
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    @printf "\r$(GREEN)Compiling So Long... [%-$(TOTAL_FILES)s] %-10s%d%%$(NC)" $$(for i in $$(seq 1 $(CURRENT_FILE)); do printf "#"; done) "" $(shell echo $$((($(CURRENT_FILE) * 100) / $(TOTAL_FILES))))
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo ""; fi
endef


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	$(call progress_bar)

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -L$(LIBFT_PATH) -lft_v2 -L$(MLX_PATH) -lmlx $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(MLX):
	@echo "$(GREEN)Compiling MLX...$(NC)"
	@$(MAKE) -C $(MLX_PATH) > /dev/null 2>&1

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Cleaned So Long objects!$(NC)"
	@$(MAKE) clean -C $(LIBFT_PATH) > /dev/null
	@echo "$(RED)Cleaned objects Libft!$(NC)"
	@$(MAKE) clean -C $(MLX_PATH) > /dev/null
	@echo "$(RED)Cleaned MLX objects!$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) fclean -C $(LIBFT_PATH) > /dev/null
	@$(MAKE) clean -C $(MLX_PATH) > /dev/null

re: fclean all

.PHONY: all clean fclean re
