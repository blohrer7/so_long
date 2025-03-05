# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 16:36:09 by blohrer           #+#    #+#              #
#    Updated: 2025/03/05 10:44:50 by blohrer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC =


OFILES = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDES = -I $(LIBFT_DIR)
LIBMLX	= ./MLX42

FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_INCLUDES = -I $(FT_PRINTF_DIR)

INCLUDES = $(LIBFT_INCLUDES) $(FT_PRINTF_INCLUDES)

all: libmlx libft ft_printf$(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR) all

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OFILES) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(FT_PRINTF) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OFILES)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBMLX)/build clean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
