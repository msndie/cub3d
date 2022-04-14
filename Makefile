# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sclam <sclam@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 22:03:23 by sclam             #+#    #+#              #
#    Updated: 2022/04/13 22:58:14 by sclam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cube3d

SRCS	=	main.c \
			srcs/map_check.c \
			srcs/map_read.c \
			srcs/utils.c \
			srcs/draw.c \

CC		=	gcc

WWW		=	-Wall -Wextra -Werror

MLX		=	-Lmlx -lmlx -framework OpenGL -framework AppKit

MLX_H	=	-Imlx

LIBFT	=	/libft/libft.a

HEAD	= 	cube3d.h

OBJS	=	${SRCS:.c=.o}

.PHONY: all clean fclean re

.c.o:
	$(CC) $(WWW) ${MLX_H} -c $< -o $@

$(NAME): $(SRCS) $(OBJS) $(HEAD)
	@make -C ./libft
	@make -C ./mlx
	$(CC) $(WWW) $(OBJS) ${MLX} -I $(HEAD) -o $(NAME) -L./libft -lft

all : $(NAME)

clean :
	rm -rf $(OBJS)
	@make clean -C ./libft

fclean : clean
	rm -rf $(NAME)
	@make fclean -C ./libft
	@make clean -C ./mlx

re : fclean all