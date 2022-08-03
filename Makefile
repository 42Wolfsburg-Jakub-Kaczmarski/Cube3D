# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 13:09:57 by kmilchev          #+#    #+#              #
#    Updated: 2022/08/03 12:30:11 by kmilchev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = Cube3d

SRCs =	src/main.c \
		src/Rendering/textures.c \
		src/Rendering/raycast.c \
		src/Rendering/render.c \
		src/Rendering/sprites.c\
		src/Rendering/sprite_rendering.c\
		src/Rendering/drawing.c \
		src/Rendering/tools.c \
		src/Movement/keys.c \
		src/Movement/arrows.c \
		src/Movement/key_hook.c \
		src/helper/get_next_line.c \
		src/helper/get_next_line_utils.c \
		src/input_validation_and_map_creation/validation.c \
		src/input_validation_and_map_creation/map_validations.c \
		src/input_validation_and_map_creation/create_map.c \
		src/input_validation_and_map_creation/check_if_map_index_exists.c \
		src/input_validation_and_map_creation/textures.c \
		src/input_validation_and_map_creation/helpers.c \
		src/input_validation_and_map_creation/helpers_2.c \
		src/input_validation_and_map_creation/set_direction.c \

OBJs := $(SRCs:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LIBS = libraries/libft.a

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJs)
	$(MAKE) -C minilbx/
	mv minilbx/libmlx.dylib .
	gcc -g $(OBJs) $(LIBS) libmlx.dylib  -framework Cocoa -framework OpenGL -framework IOKit -o Cube3d

clean:
	$(MAKE) clean -C minilbx/
	rm -f $(OBJs)

fclean: clean
	rm -f libmlx.dylib 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test