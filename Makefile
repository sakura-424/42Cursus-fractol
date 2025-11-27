# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/23 07:30:10 by skatsuya          #+#    #+#              #
#    Updated: 2025/11/27 21:27:46 by skatsuya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror -I libft -I include -I minilibx-linux -O2
RM = rm -rf

# for MAC
# MLX_FLAGS = -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit
# # for Linux
MLX_FLAGS = -I minilibx-linux -L minilibx-linux -lmlx -lXext -lX11 -lm
LIBFT = -L libft -lft

SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = main.c \
            user_help.c \
            color.c \
            draw_fractol.c \
            events.c \
            ft_atof.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) make_libft
	$(CC) $(OBJS) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

make_libft:
	make -C libft

clean:
	$(RM) $(OBJ_DIR)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
