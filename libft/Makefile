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


NAME		=	libft.a
CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
INCLUDE 	=	-I includes

SRC_FILE	=	ft_atoi.c \
				ft_atoi_str.c \
				ft_bigputnbr.c \
				ft_bzero.c \
				safe_malloc.c \
				ft_clear_tab.c \
				ft_errexit.c \
				ft_fabs.c \
				ft_free_tab.c \
				ft_getfile.c \
				ft_int_strchr.c \
				ft_int_strdup.c \
				ft_intswap.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isdigit_str.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_listlen.c \
				ft_lstnew.c \
				ft_memalloc.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memdel.c \
				ft_memmove.c \
				ft_memset.c \
				ft_nputchar.c \
				ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl.c \
				ft_putendl_fd.c \
				ft_putnbr.c \
				ft_putnbrendl.c \
				ft_putnbr_fd.c \
				ft_putstr.c \
				ft_putstr_color.c \
				ft_putstr_fd.c \
				ft_puttab.c \
				ft_sort_int_tab.c \
				ft_sqrt.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strclr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdel.c \
				ft_strdup.c \
				ft_strequ.c \
				ft_striter.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strjoin_free.c \
				ft_strlcat.c \
				ft_strlen.c \
				ft_strmap.c \
				ft_strmapi.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strndup.c \
				ft_strnequ.c \
				ft_strnew.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strsplit.c \
				ft_strstr.c \
				ft_strsub.c \
				ft_strswap.c \
				ft_strtrim.c \
				ft_strtrim_extended.c \
				ft_tabdel.c \
				ft_tabjoin.c \
				ft_tablen.c \
				ft_tolower.c \
				ft_toupper.c \
				get_next_line.c \
				remove_list.c

SRC_DIR		=	src
OBJ_DIR		=	obj
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILE))
OBJ			=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILE))

.PHONY: all compile clean fclean re

all: compile

$(NAME): $(SRC) $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


compile:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
