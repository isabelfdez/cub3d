# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/03 17:42:48 by isfernan          #+#    #+#              #
#    Updated: 2020/09/10 17:50:42 by isfernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	cub3d.c	draw.c	textures.c	sprites.c	screenshot.c	inputs.c \
		./utils/*.c		./libft/*.c			./get_next_line/*.c	\
		inputs2.c	create_map.c	check_map.c	raycasting.c	press_key.c \
		movement.c	managers.c		release_key.c

OBJS = ${SRCS:.c=.o}

NAME = cub3D

FLAGS = -Wall -Werror -Wextra -I /usr/local/include

$(NAME): 
			-@cc ${FLAGS} ${SRCS} -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
			-@rm -f $(OBJS)

fclean: 	clean
			-@rm -f $(NAME)

re:	fclean all

.PHONY: all clea fclean re
