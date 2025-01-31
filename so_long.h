#ifndef SO_LONG_H
# define SO_LONG_H

# include "inc/gnl/get_next_line.h"
# include "inc/libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;

	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collect_count;
	int		collected;
	int		moves;

	void	*wall_img;
	void	*floor_img;
	void	*player_img;
	void	*collect_img;
	void	*exit_img;

	int		tile_size;
}			t_game;

char		**parse_map(const char *filename, t_game *game);
bool		check_map_basic(t_game *game);
bool		check_map_path(t_game *game);

void		draw_map(t_game *game);

int			handle_keypress(int keycode, t_game *game);
int			handle_close(t_game *game);

void		free_map(char **map, int height);
int			quit_game(t_game *game);

#endif