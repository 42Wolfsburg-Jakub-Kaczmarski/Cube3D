NAME = Cube3d

SRCs = main.c \
		src/Rendering/textures.c \
		src/Rendering/raycast.c \
		src/Rendering/render.c \
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

CFLAGS = -Wall -Wextra -Werror;

LIBS = libmlx.dylib libft.a

all: $(NAME)

Cube3d:
	gcc -g $(SRCs) $(LIBS) -framework Cocoa -framework OpenGL -framework IOKit -o Cube3d

clean:
	@rm -f $(NAME)
fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test