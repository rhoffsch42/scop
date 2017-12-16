# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/15 17:38:19 by rhoffsch          #+#    #+#              #
#    Updated: 2017/07/03 16:41:53 by rhoffsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	scop
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g

SDL_DST			=	SDL
INCLUDE			=	-I includes -I libft/includes -I ./$(SDL_DST)/include -I /usr/include
SDL				=	`./$(SDL_DST)/bin/sdl2-config --cflags --libs` -lSDL2_image


CFILE			=	main.c \
					init1.c \
					init2.c \
					load_file.c \
					manage_file.c \
					manage_file2.c \
					link_file.c \
					obj_build.c\
					obj_data.c \
					obj_data2.c \
					obj_checks.c \
					mtl_build.c \
					mtl_data.c \
					mtl_checks.c \
					string.c \
					ft_free_list.c \
					free_struct1.c \
					free_struct2.c \
					for_list.c \
					list_to_tab.c \
					sdl_putpixel.c \
					display.c \
					event.c \
					xpm_load.c \
					xpm_data.c \
					xpm_to_glid.c \
					data_parsing.c \
					color.c \
					misc.c

HFILE			=	scop.h

HDIR			=	includes/
HDR				=	$(patsubst %.h, $(HDIR)%.h, $(HFILE))
SDIR			=	src/
SRC				=	$(patsubst %.c, $(SDIR)%.c, $(CFILE))
ODIR			=	obj/
OBJ				=	$(patsubst %.c, $(ODIR)%.o, $(CFILE))

.PHONY: all compile lib norm clean fclean pclean re

all: compile

compile: lib sdl
	@mkdir -p $(ODIR)
	@$(MAKE) $(NAME)

lib:
	@$(MAKE) -C libft/

sdl:
	@$(MAKE) -f Makefile.sdl

$(NAME): $(SRC) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L libft/ -lft $(SDL) -lGL -lGLU #-lglut
	@echo "\033[33;32m$(NAME) \033[33;37mcompiled"
	@echo "\033[33;35m$(NAME) End\033[33;37m"

$(ODIR)%.o: $(SDIR)%.c $(HDR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[33;33m\t$@ compiled\033[33;37m"


norm:
	norminette $(SRC) $(HDR)

clean:
	@rm -rf $(ODIR)
	@echo "\033[33;33mAll objects \033[33;31mdeleted\033[33;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33;32m$(NAME) \033[33;31mdeleted\033[33;37m"

pclean: fclean
	make fclean -C ./libft/
	make fclean -f Makefile.sdl

re: fclean all
