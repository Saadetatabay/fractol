SRC = ft_fractol.c ft_utilis.c event.c
OBJ = $(SRC:.c=.o)
NAME = fractol
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g3

all : mlx $(NAME)

mlx : 
	make -C minilibx-linux 

$(NAME) : $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -Iminilibx-linux -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz -o ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re :fclean all

.PHONY : all clean fclean re