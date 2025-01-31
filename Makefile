NAME        = so_long
CC          = cc
CFLAGS      = #-Wall -Wextra -Werror

# MLX on macOS with frameworks:
MLX_FLAGS   = -L./mlx -lmlx -framework OpenGL -framework AppKit

# If on Linux, you might need something like:
# MLX_FLAGS = -L ./mlx -lmlx -lXext -lX11 -lm -lz

SRCS        = main.c \
              map_parser.c \
              map_checker.c \
              draw.c \
              hooks.c \
              free_utils.c \
			  inc/gnl/get_next_line.c \
       		  inc/gnl/get_next_line_utils.c

OBJS        = $(SRCS:.c=.o)

# Path to your libft directory and library:
LIBFT_DIR   = inc/libft
LIBFT       = $(LIBFT_DIR)/libft.a

# -----------------------------------------------------------------------------
#                               MAIN TARGETS
# -----------------------------------------------------------------------------
all: $(NAME)

# so_long depends on both the object files and the libft library
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

# -----------------------------------------------------------------------------
#                              COMPILE OBJECTS
# -----------------------------------------------------------------------------
%.o: %.c
	$(CC) $(CFLAGS) -Imlx -I$(LIBFT_DIR) -c $< -o $@

# -----------------------------------------------------------------------------
#                              LIBFT TARGET
# -----------------------------------------------------------------------------
# If your libft Makefile is in inc/libft/ and produces libft.a, you can build it:
$(LIBFT):
	make -C $(LIBFT_DIR)

# -----------------------------------------------------------------------------
#                               CLEAN TARGETS
# -----------------------------------------------------------------------------
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
