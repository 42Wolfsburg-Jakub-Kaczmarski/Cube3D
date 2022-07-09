NAME = Cube3d

SRCs = main.c ray_casting.c get_next_line.c get_next_line_utils.c keys.c

OBJS = $(SRCs:.c=.o)

Libraries =	../../libraries/libmlx42.a \
			../../libraries/libglfw3.a \
			../../libraries/libft.a
FLAGS = -Wall -Wextra -Werror 
# test:
# 	gcc ray_casting.c libmlx42.a libglfw3.a libft.a -framework Cocoa -framework OpenGL -framework IOKit -o kk
all: $(NAME)
	./Cube3d
Cube3d: $(OBJS)
	gcc $(OBJS) $(Libraries) -framework Cocoa -framework OpenGL -framework IOKit -o Cube3d
	

clean:
	@rm -f $(NAME)
	@rm -f $(OBJS)
fclean:
	@rm -f $(NAME)

re: fclean all

remix: fclean test
	./kk

memory:
	leaks --atExit -- ./Cube3d
.PHONY: all clean fclean re test