/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihakan <yihakan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:27:54 by yihakan           #+#    #+#             */
/*   Updated: 2025/03/16 00:45:15 by yihakan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

int	quit_game(t_game *game)
{
	if (game->map)
		free_map(game->map, game->height);
	if (game->win)
	{
		if (game->wall_img)
			mlx_destroy_image(game->mlx, game->wall_img);
		if (game->floor_img)
			mlx_destroy_image(game->mlx, game->floor_img);
		if (game->player_img)
			mlx_destroy_image(game->mlx, game->player_img);
		if (game->collect_img)
			mlx_destroy_image(game->mlx, game->collect_img);
		if (game->exit_img)
			mlx_destroy_image(game->mlx, game->exit_img);
		mlx_destroy_window(game->mlx, game->win);
	}
	if (game->mlx)
	{
		//mlx_destroy_display(game->mlx);
		free (game->mlx);
	}
	return (0);
}
