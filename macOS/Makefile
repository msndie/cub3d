# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sclam <sclam@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 22:03:23 by sclam             #+#    #+#              #
#    Updated: 2022/06/01 14:06:43 by sclam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

NAME_B	=	cub3D_bonus

SRCS	=	srcs/main.c \
			srcs/draw.c \
			srcs/input.c \
			srcs/map_check.c \
			srcs/map_read.c \
			srcs/movement.c \
			srcs/raycast.c \
			srcs/utils.c \
			srcs/dda.c \
			srcs/loop_hook.c \
			srcs/map_to_int.c \
			srcs/map_walls_check.c \
			srcs/parse_assets.c

SRCS_B	=	srcs_bonus/dda.c \
			srcs_bonus/doors_bonus.c \
			srcs_bonus/doors_hit.c \
			srcs_bonus/draw_bonus.c \
			srcs_bonus/input_bonus.c \
			srcs_bonus/list_bonus.c \
			srcs_bonus/loop_hook.c \
			srcs_bonus/main_bonus.c \
			srcs_bonus/map_check_bonus.c \
			srcs_bonus/map_read_bonus.c \
			srcs_bonus/map_to_int.c \
			srcs_bonus/map_walls_check.c \
			srcs_bonus/minimap.c \
			srcs_bonus/mouse_bonus.c \
			srcs_bonus/movement_bonus.c \
			srcs_bonus/parse_assets.c \
			srcs_bonus/raycast_bonus.c \
			srcs_bonus/sort_list_bonus.c \
			srcs_bonus/sprites_bonus.c \
			srcs_bonus/utils_bonus.c

UNION_S	=	srcs/draw_utils.c \
			srcs/colour_parse.c

CC		=	gcc

WWW		=	-Wall -Wextra -Werror

MLX		=	-Lmlx -lmlx -framework OpenGL -framework AppKit

MLX_H	=	-Imlx

LIBFT	=	/libft/libft.a

HEAD	= 	./incs/cub3d.h

HEAD_B	= 	./incs/cub3d_bonus.h

OBJS	=	${SRCS:.c=.o} ${UNION_S:.c=.o}

OBJS_B	=	${SRCS_B:.c=.o} ${UNION_S:.c=.o}

.PHONY: all clean fclean re

.c.o:
	$(CC) $(WWW) -c $< -o $@

$(NAME): $(SRCS) $(UNION_S) $(OBJS) $(HEAD)
	@make -C ./libft
	@make -C ./mlx
	$(CC) $(WWW) $(OBJS) ${MLX} -I $(HEAD) -o $(NAME) -L./libft -lft

$(NAME_B): $(SRCS_B) $(UNION_S) $(OBJS_B) $(HEAD_B)
	@make -C ./libft
	@make -C ./mlx
	$(CC) $(WWW) $(OBJS_B) ${MLX} -I $(HEAD_B) -o $(NAME_B) -L./libft -lft

all : $(NAME)

bonus : $(NAME_B)

clean :
	rm -rf $(OBJS)
	rm -rf $(OBJS_B)
	@make clean -C ./libft

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME_B)
	make fclean -C ./libft
	@make clean -C ./mlx

re : fclean all