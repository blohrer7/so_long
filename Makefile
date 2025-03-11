# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 13:18:56 by blohrer           #+#    #+#              #
#    Updated: 2025/03/11 11:44:28 by blohrer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GAME        = so_long

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

MLX_PATH    = ./lib/MLX42
LIBFT_PATH  = ./lib/libft
PRINTF_PATH = ./lib/ft_printf

INCLUDES    = -I ./include -I $(MLX_PATH)/include -I $(LIBFT_PATH)

LIBRARIES   = $(MLX_PATH)/build/libmlx42.a \
               -L$(LIBFT_PATH) -lft \
               -L$(PRINTF_PATH) -lftprintf \
               -ldl -lglfw -pthread -lm

SRC_DIR     = src
SRC_FILES   =	main.c \
				map_check.c \
				player.c \
				map_load.c \
				player_move.c \
				utils.c

SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(SRCS:.c=.o)

all: libft mlx $(GAME)
	@echo "\n\033[1;33m🚀 Use: ./so_long src/maps/YOUR_MAP.ber\033[0m\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "\033[1;32m✔ Compiled: $<\033[0m"

$(GAME): libft $(OBJS)
	@$(CC) $(OBJS) $(LIBRARIES) -o $(GAME)
	@echo "\n\033[1;36m $(GAME) compiled successfully!\033[0m\n"

libft:
	@make -C $(LIBFT_PATH)
	@make -C $(PRINTF_PATH)

mlx:
	@cmake $(MLX_PATH) -B $(MLX_PATH)/build
	@make -C $(MLX_PATH)/build -j4

clean:
	@rm -f $(OBJS)
	@rm -rf $(MLX_PATH)/build
	@make -C $(LIBFT_PATH) clean
	@make -C $(PRINTF_PATH) clean
	@echo "\033[1;33m Cleaned up objects & MLX42!\033[0m"

fclean: clean
	@rm -f $(GAME)
	@make -C $(LIBFT_PATH) fclean
	@make -C $(PRINTF_PATH) fclean
	@echo "\033[1;33m Fully cleaned $(GAME)!\033[0m"

re: fclean all

.PHONY: all clean fclean re libft mlx
