# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/10 20:07:50 by rhoffsch          #+#    #+#              #
#    Updated: 2016/02/10 02:48:29 by rhoffsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	libmath3d.a
CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
INCLUDE 	=	-I includes

SRC_FILE	=	print.c \
				vector2.c \
				vector2_add.c \
				vector2_sub.c \
				vector2_mult_coef.c \
				vector2_magnitude.c \
				vector2_dot.c \
				vector2_rot.c \
				vector3.c \
				vector3_add.c \
				vector3_sub.c \
				vector3_mult_coef.c \
				vector3_magnitude.c \
				vector3_dot.c \
				vector3_cross.c \
				vector3_rot.c \
				matrix4.c \
				matrix4_set_order.c \
				matrix4_cpy.c \
				matrix4_add.c \
				matrix4_sub.c \
				matrix4_mult.c \
				matrix4_mult_coef.c

HDR_FILE	=	libmath3d.h

SRC_DIR		=	src
OBJ_DIR		=	obj
HDR_DIR		=	includes
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILE))
OBJ			=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILE))
HDR			=	$(addprefix $(HDR_DIR)/, $(HDR_FILE))

.PHONY: all compile clean fclean re

all: compile

$(NAME): $(SRC) $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

compile:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
