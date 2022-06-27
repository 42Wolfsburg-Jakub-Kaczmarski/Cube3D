NAME = Cube3d

all: $(NAME)

Cube3d:
	gcc -Wall -Wextra -Werror main.c map_check.c get_next_line.c get_next_line_utils.c libmlx42.a libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -o Cube3d

clean:
	@rm -f $(NAME)
fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re