/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihakan <yihakan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:23:59 by yihakan           #+#    #+#             */
/*   Updated: 2025/02/25 14:39:36 by yihakan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "inc/gnl/get_next_line.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

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
int			check_map_basic(t_game *game);
int			check_map_path(t_game *game);

void		draw_map(t_game *game);

int			handle_keypress(int keycode, t_game *game);
int			handle_close(t_game *game);

void		free_map(char **map, int height);
int			quit_game(t_game *game);

int			ft_strlen_int(const char *s);
int			check_map_walls(t_game *game);
int			count_map_elements(t_game *game, int *p_count, int *e_count,
				int *c_count);
void		flood_fill(char **visited, int x, int y, t_game *game);
int			check_reachable(char **visited, t_game *game);
int			init_visited_map(t_game *game, char ***visited);

void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
int			check_ext(char *map);

#endif