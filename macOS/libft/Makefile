# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sclam <sclam@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 15:41:45 by sclam             #+#    #+#              #
#    Updated: 2022/03/10 15:26:42 by sclam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c \
			ft_strlen.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_strchr.c \
			ft_strdup.c ft_striteri.c ft_strjoin.c \
			ft_strlcat.c ft_strlcpy.c ft_strmapi.c \
			ft_strncmp.c ft_strnstr.c ft_strrchr.c \
			ft_substr.c ft_tolower.c ft_toupper.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_strtrim.c ft_itoa.c ft_split.c \
			ft_free_arr.c gnl/get_next_line.c ft_realloc.c \
			ft_char_arr_len.c ft_put_char_arr_fd.c \
			ft_strjoin_free.c

NAME	=	libft.a

CC		=	cc

OBJS	=	${SRCS:.c=.o}

ARLIB	=	@ar r

RANLIB	=	ranlib

RM		=	rm -f

HEAD	=	libft.h

%.o : %.c	${HEAD}
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HEAD}

${NAME}:	${OBJS} ${HEAD}
			@${ARLIB} ${NAME} ${OBJS}
			@${RANLIB} ${NAME}

all:		${NAME}

clean:
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re