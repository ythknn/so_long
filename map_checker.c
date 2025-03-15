/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihakan <yihakan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:21:16 by yihakan           #+#    #+#             */
/*   Updated: 2025/03/16 02:32:55 by yihakan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_basic(t_game *game)
{
	int	player_count;
	int	exit_count;
	int	collect_count;

	player_count = 0;
	exit_count = 0;
	collect_count = 0;
	if (!check_map_walls(game))
	{
		write(1, "error: map walls not correct\n", 29);
		return (0);
	}
	if (!count_map_elements(game, &player_count, &exit_count, &collect_count))
		return (0);
	if (player_count != 1 || exit_count != 1 || collect_count < 1)
	{
		write(1, "error: map element count not correct\n", 37);
		return (0);
	}
	game->collect_count = collect_count;
	return (1);
}

int	check_map_path(t_game *game)
{
	char	**visited;
	int		result;
	int		i;

	if (!init_visited_map(game, &visited))
		return (0);
	flood_fill(visited, game->player_x, game->player_y, game);
	result = check_reachable(visited, game);
	i = 0;
	while (i < game->height)
		free(visited[i++]);
	free(visited);
	return (result);
}

int	ft_strlen_int(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
