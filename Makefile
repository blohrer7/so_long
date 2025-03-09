# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 16:36:09 by blohrer           #+#    #+#              #
#    Updated: 2025/03/09 07:19:26 by blohrer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long
CFLAGS		= -Wextra -Wall -Werror
LIBMLX		= ./lib/MLX42
LIBFT		= ./lib/libft
LIBPRINTF	= ./lib/ft_printf

HEADERS		= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		= $(LIBMLX)/build/libmlx42.a -L$(LIBFT) -lft -L$(LIBPRINTF) -lftprintf -ldl -lglfw -pthread -lm

SRCS		=	src/main.c \
				src/map_check.c \
				src/player.c \
				src/map_load.c \
				src/player_move.c \
				src/utils.c

OBJS		= ${SRCS:.c=.o}

all: libft libmlx $(NAME)
	@echo " "
	@echo "\033[38;5;214mStart the game with ./so_long maps/MAP_OF_CHOICE.ber\033[0m"

libft:
	@make -C $(LIBFT)
	@make -C $(LIBPRINTF)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "\033[32mCompiled $<\033[0m"

$(NAME): libft $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean
	@make -C $(LIBPRINTF) clean
	@echo "\033[38;5;214mCleaned MLX42\033[0m"
	@echo "\033[38;5;214mCleaned so_long\033[0m"

fclean:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) fclean
	@make -C $(LIBPRINTF) fclean
	@echo "\033[38;5;214mFcleaned MLX42\033[0m"
	@echo "\033[38;5;214mFcleaned $(NAME)\033[0m"

re: fclean all

.PHONY: all clean fclean re libft libmlx
