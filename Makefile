NAME = Cube3d

SRCs = main.c ray_casting.c get_next_line.c get_next_line_utils.c keys.c

Libraries =	libraries/libmlx42.a \
			libraries/libglfw3.a \
			libraries/libft.a
FLAGS = -Wall -Wextra -Werror 
# test:
# 	gcc ray_casting.c libmlx42.a libglfw3.a libft.a -framework Cocoa -framework OpenGL -framework IOKit -o kk
all: $(NAME)
	./Cube3d
Cube3d:
	gcc $(SRCs) $(Libraries) -framework Cocoa -framework OpenGL -framework IOKit -o Cube3d
	

clean:
	@rm -f $(NAME)
fclean:
	@rm -f $(NAME)

re: fclean all

remix: fclean test
	./kk

memory:
	leaks --atExit -- ./Cube3d
.PHONY: all clean fclean re test