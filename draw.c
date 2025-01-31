/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihakan <yihakan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:24:14 by yihakan           #+#    #+#             */
/*   Updated: 2025/01/31 20:05:50 by yihakan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * game->tile_size, y
			* game->tile_size);
}

static void	draw_tile(t_game *game, int x, int y)
{
	char	current;

	put_image(game, game->floor_img, x, y);
	current = game->map[y][x];
	if (current == '1')
		put_image(game, game->wall_img, x, y);
	else if (current == 'C')
		put_image(game, game->collect_img, x, y);
	else if (current == 'E')
		put_image(game, game->exit_img, x, y);
	if (x == game->player_x && y == game->player_y)
		put_image(game, game->player_img, x, y);
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	mlx_clear_window(game->mlx, game->win);
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_tile(game, x, y);
			x++;
		}
		y++;
	}
}
