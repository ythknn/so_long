/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihakan <yihakan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:10:48 by yihakan           #+#    #+#             */
/*   Updated: 2025/01/31 02:23:55 by yihakan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->win = mlx_new_window(game->mlx, game->width * game->tile_size,
			game->height * game->tile_size, "so_long");
	if (!game->win)
		return (false);
	return (true);
}

static bool	load_textures(t_game *game)
{
	int	w;
	int	h;

	game->wall_img = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &w,
			&h);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "./textures/floor.xpm",
			&w, &h);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm",
			&w, &h);
	game->collect_img = mlx_xpm_file_to_image(game->mlx,
			"./textures/collect.xpm", &w, &h);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "./textures/exit.xpm", &w,
			&h);
	if (!game->wall_img || !game->floor_img || !game->player_img
		|| !game->collect_img || !game->exit_img)
		return (false);
	return (true);
}

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->collect_count = 0;
	game->collected = 0;
	game->moves = 0;
	game->tile_size = 64;
}

static bool	setup_game(t_game *game, char *map_path)
{
	game->map = parse_map(map_path, game);
	if (!game->map || !check_map_basic(game) || !check_map_path(game))
		return (false);
	if (!init_window(game) || !load_textures(game))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./so_long <map.ber>\n", 33);
		return (1);
	}
	init_game(&game);
	if (!setup_game(&game, argv[1]))
	{
		write(2, "Error\nFailed to initialize game.\n", 33);
		quit_game(&game);
		return (1);
	}
	draw_map(&game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_loop(game.mlx);
	return (0);
}
