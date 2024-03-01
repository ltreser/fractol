# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 05:57:35 by ltreser           #+#    #+#              #
#    Updated: 2024/02/24 23:05:30 by ltreser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = main.c hooks.c

SRC_DIR = src/

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

INC_DIR = include/

HEADERS = $(addprefix $(INC_DIR), fractol.h)

CC = cc

CFLAGS = -Wall -Werror -Wextra -Iinclude/ -I/usr/include -Iminilibx-linux -O3

LDLIBS = -lft -lmlx

LDFLAGS = -L libft -L minilibx-linux

LFLAGS = -lbsd -lXext -lX11 -lm

RM = rm -rf

LIBFT = libft/libft.a

LIBMLX = minilibx-linux/libmlx_Linux.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I/usr/include -Imlx_linux -O3 -c  $< -o $@

$(LIBFT):
	make -C ./libft

$(LIBMLX):
	git clone https://github.com/42Paris/minilibx-linux.git minilibx-linux
	make -C minilibx-linux

$(NAME): $(HEADERS) $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS) $(LFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean
	$(RM) minilibx-linux
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
