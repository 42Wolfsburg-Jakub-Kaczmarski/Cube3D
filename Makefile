NAME = Cube3d

SRCs = main.c Rendering/textures.c Rendering/raycast.c Rendering/render.c Rendering/drawing.c Rendering/tools.c Movement/keys.c Movement/arrows.c Movement/key_hook.c src/helper/get_next_line.c src/helper/get_next_line_utils.c \
		src/input_validation_and_map_creation/validation.c \
		src/input_validation_and_map_creation/map_validations.c \
		src/input_validation_and_map_creation/create_map.c \
		src/input_validation_and_map_creation/check_if_map_index_exists.c \
		src/input_validation_and_map_creation/textures.c \
		src/input_validation_and_map_creation/helpers.c \
		src/input_validation_and_map_creation/helpers_2.c \

all: $(NAME)

Cube3d:
	gcc -g -Wall -Wextra -Werror $(SRCs) libmlx.dylib -framework Cocoa -framework OpenGL -framework IOKit libft.a -o Cube3d

clean:
	@rm -f $(NAME)
fclean:
	@rm -f $(NAME)

re: fclean all

test:
	gcc -Wall -Wextra -Werror main.c Movement/keys.c libmlx42.a libglfw3.a libft.a -framework Cocoa -framework OpenGL -framework IOKit -fsanitize=address -o test

test1:
	gcc -Wall -Wextra -Werror test.c libmlx42.a libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -fsanitize=address -o test1

.PHONY: all clean fclean re test