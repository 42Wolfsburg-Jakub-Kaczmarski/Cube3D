NAME = Cube3d

SRCs = main.c Movement/keys.c Movement/arrows.c Movement/key_hook.c get_next_line.c get_next_line_utils.c keys.c draw.c

all: $(NAME)

Cube3d:
	gcc -Wall -Wextra -Werror $(SRCs) libmlx.dylib -framework Cocoa -framework OpenGL -framework IOKit -o Cube3d

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