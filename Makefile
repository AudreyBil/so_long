NAME = solong
LIBFTNAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFTPATH = ./libft

SRCS = main.c			\
	read_map.c			\
	valid_map.c			\
	valid_map2.c		\
	free_memory.c		\
	flood_fill.c		\
	render_game.c		\


OBJS = $(SRCS:.c=.o)
MLX_LIB = mlx/
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

all: $(NAME)

makelibft:
	@make -C $(LIBFTPATH)
	@cp $(LIBFTPATH)/$(LIBFTNAME) .
	@mv $(LIBFTNAME) $(NAME)

$(NAME): makelibft $(OBJS)
	@if [ ! -d "mlx" ]; then \
	git clone https://github.com/42Paris/minilibx-linux.git mlx; \
	fi
	@make -C $(MLX_LIB)
	$(CC) $(OBJS) -L./libft -lft $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $^ -o $@

clean:
	@rm -f $(OBJS)
	@cd $(LIBFTPATH) && make clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_LIB)
	@cd $(LIBFTPATH) && make fclean

re: fclean all

.PHONY: all clean fclean re libft
