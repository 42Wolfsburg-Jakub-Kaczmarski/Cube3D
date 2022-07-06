NAME = Cube3d

SRCs = main.c map_check.c get_next_line.c get_next_line_utils.c keys.c draw.c

test:
	gcc ray_casting.c libmlx42.a libglfw3.a libft.a -framework Cocoa -framework OpenGL -framework IOKit -o kk
all: $(NAME)

Cube3d:
	gcc -Wall -Wextra -Werror $(SRCs) libmlx42.a libglfw3.a libft.a -framework Cocoa -framework OpenGL -framework IOKit -o Cube3d

clean:
	@rm -f $(NAME)
fclean:
	@rm -f $(NAME)

re: fclean all

remix: fclean test
	./kk
.PHONY: all clean fclean re test