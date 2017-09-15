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


NAME	=	libft.a
CFLAGS	=	-Wall -Wextra -Werror -g
CC		=	gcc
INCLUDE =	-I includes

CFILE	=	ft_atoi.c \
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
			get_next_line.c

SDIR	=	src/
SRC		=	$(patsubst %.c, $(SDIR)%.c, $(CFILE))
ODIR	=	obj/
OBJ		=	$(patsubst %.c, $(ODIR)%.o, $(CFILE))

all: compile

$(NAME): $(SRC) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "\033[33;32m$(NAME) \033[33;37mcreated"
	@ranlib libft.a
	@echo Index created
	@echo "\033[33;35mlibft.a End \033[33;37m"

$(ODIR)%.o: $(SDIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[33;33m \tlibft/$@ compiled \033[33;37m"

compile:
		@mkdir -p obj/
		@$(MAKE) $(NAME)

norm:
	norminette $(SRC) $(HDR)

clean:
	@rm -rf $(ODIR)
	@echo "\033[33;33mAll objects  \033[33;31mdeleted \033[33;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33;32m$(NAME)  \033[33;31mdeleted \033[33;37m"

re: fclean all
