# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/15 17:38:19 by rhoffsch          #+#    #+#              #
#    Updated: 2018/03/07 10:24:31 by rhoffsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	scop
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g

INCLUDE			=	-I includes \
					-I libft/includes -I libmath3d/includes \
					-I /Users/rhoffsch/.brew/Cellar/glfw/3.2.1/include \
					-I /Users/rhoffsch/.brew/Cellar/glew/2.1.0/include

LIBS			=	-L libft/ -lft -L libmath3d/ -lmath3d

FRAMEWORKS		=	-framework OpenGL

GLFW			=	/Users/rhoffsch/.brew/Cellar/glfw/3.2.1/lib/libglfw.dylib
GLEW			=	/Users/rhoffsch/.brew/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib

SRC_FILE		=	main.c \
					dump_data.c \
					init1.c \
					init2.c \
					load_file.c \
					manage_file.c \
					manage_file2.c \
					link_file.c \
					obj_build.c\
					obj_data.c \
					obj_data2.c \
					triangularize_face.c \
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
					display.c \
					matrix.c \
					gl_error.c \
					gl_build.c \
					gl_obj3d.c \
					gl_skybox.c \
					gl_init.c \
					gl_update.c \
					gl_fill_arrays.c \
					event.c \
					event2.c \
					xpm_load.c \
					xpm_data.c \
					xpm_to_glid.c \
					data_parsing.c \
					color.c \
					misc.c

HDR_FILE		=	scop.h \
					scop_struct.h \
					scop_opengl.h

SRC_DIR			=	src
OBJ_DIR			=	obj
HDR_DIR			=	includes
SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_FILE))
OBJ				=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILE))
HDR				=	$(addprefix $(HDR_DIR)/, $(HDR_FILE))

.PHONY: all compile lib clean fclean pclean re

all: compile

compile: lib
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME)

lib:
	@$(MAKE) -C libft/
	@$(MAKE) -C libmath3d/

$(NAME): $(SRC) $(OBJ) libft/libft.a libmath3d/libmath3d.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS) $(FRAMEWORKS) $(GLFW) $(GLEW)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

pclean: fclean
	@$(MAKE) fclean -C libft/
	@$(MAKE) fclean -C libmath3d/

re: fclean all
