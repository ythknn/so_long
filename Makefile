NAME        = so_long
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I./mlx

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    MLX_URL = https://cdn.intra.42.fr/document/document/31098/minilibx_opengl.tgz
    MLX_FLAGS = -L./mlx -lmlx -framework OpenGL -framework AppKit
else
    MLX_URL = https://cdn.intra.42.fr/document/document/31097/minilibx-linux.tgz
    MLX_FLAGS = -L ./mlx -lmlx -lXext -lX11 -lm -lz
endif


SRCS        = so_long.c \
              map_parser.c \
              map_checker.c \
			  map_utils.c \
              draw.c \
              hooks.c \
              free_utils.c \
			  utils.c \
			  inc/gnl/get_next_line.c \
       		  inc/gnl/get_next_line_utils.c


# -----------------------------------------------------------------------------
#                               MAIN TARGETS
# -----------------------------------------------------------------------------
all: mlx $(NAME)

$(NAME): $(SRCS) mlx
	$(CC) $(CFLAGS) $(SRCS) $(MLX_FLAGS) -o $(NAME)

mlx:
	@if [ ! -d "mlx" ]; then \
		curl -o minilibx.tgz $(MLX_URL); \
		tar -xzf minilibx.tgz; \
		rm -f minilibx.tgz; \
		mv minilibx* mlx; \
		cd mlx && make; \
	echo "MiniLibX downloaded and built."; \
	fi

# -----------------------------------------------------------------------------
#                               CLEAN TARGETS
# -----------------------------------------------------------------------------
clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
