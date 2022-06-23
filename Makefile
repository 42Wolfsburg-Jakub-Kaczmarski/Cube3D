all: Cube3d

Cube3d:
	gcc -Wall -Wextra -Werror main.c libmlx42.a libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -o Cube3d

clean:
	@rm -f so_long
fclean:
	@rm -f so_long
re: fclean all

.PHONY: all clean fclean re