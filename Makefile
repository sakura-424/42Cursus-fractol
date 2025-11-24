# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skatsuya <skatsuya@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/23 07:30:10 by skatsuya          #+#    #+#              #
#    Updated: 2025/11/25 01:38:13 by skatsuya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror -I libft -O2

# MLX_FLAGS = -I minilibx_linux -L minilibx_linux -lmlx -lXext -lX11 -lm

MLX_FLAGS = -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit
LIBFT = -L libft -lft
SRCS = main.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) make_libft
	$(CC) $(OBJS) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -I minilibx_linux -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I minilibx -c $< -o $@

make_libft:
	make -C libft

all: $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
