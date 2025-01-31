/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihakan <yihakan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:28:06 by yihakan           #+#    #+#             */
/*   Updated: 2025/01/31 02:30:50 by yihakan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	check_map_walls(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->height)
	{
		col = 0;
		while (game->map[row][col])
			col++;
		if (col != game->width)
			return (false);
		if (game->map[row][0] != '1' || game->map[row][game->width - 1] != '1')
			return (false);
		row++;
	}
	col = 0;
	while (col < game->width)
	{
		if (game->map[0][col] != '1' || game->map[game->height - 1][col] != '1')
			return (false);
		col++;
	}
	return (true);
}

static bool	count_map_elements(t_game *game, int *p_count, int *e_count,
		int *c_count)
{
	int		row;
	int		col;
	char	c;

	row = 0;
	while (row < game->height)
	{
		col = 0;
		while (col < game->width)
		{
			c = game->map[row][col];
			if (c == 'P')
			{
				(*p_count)++;
				game->player_x = col;
				game->player_y = row;
			}
			else if (c == 'E')
				(*e_count)++;
			else if (c == 'C')
				(*c_count)++;
			else if (c != '0' && c != '1')
				return (false);
			col++;
		}
		row++;
	}
	return (true);
}

bool	check_map_basic(t_game *game)
{
	int	player_count;
	int	exit_count;
	int	collect_count;

	player_count = 0;
	exit_count = 0;
	collect_count = 0;
	if (!check_map_walls(game))
		return (false);
	if (!count_map_elements(game, &player_count, &exit_count, &collect_count))
		return (false);
	if (player_count != 1 || exit_count != 1 || collect_count < 1)
		return (false);
	game->collect_count = collect_count;
	return (true);
}

static void	flood_fill(char **visited, int x, int y, t_game *game)
{
	if (y < 0 || y >= game->height || x < 0 || x >= game->width)
		return ;
	if (visited[y][x] == '1' || visited[y][x] == 'X')
		return ;
	visited[y][x] = 'X';
	flood_fill(visited, x + 1, y, game);
	flood_fill(visited, x - 1, y, game);
	flood_fill(visited, x, y + 1, game);
	flood_fill(visited, x, y - 1, game);
}

static bool	check_reachable(char **visited, t_game *game)
{
	int	i;
	int	j;
	int	reachable_c;
	int	reachable_e;

	reachable_c = 0;
	reachable_e = 0;
	j = 0;
	while (j < game->height)
	{
		i = 0;
		while (i < game->width)
		{
			if (game->map[j][i] == 'C' && visited[j][i] == 'X')
				reachable_c++;
			if (game->map[j][i] == 'E' && visited[j][i] == 'X')
				reachable_e++;
			i++;
		}
		j++;
	}
	return (reachable_c == game->collect_count && reachable_e == 1);
}

bool	check_map_path(t_game *game)
{
	int		i;
	char	**visited;
	bool	result;

	visited = malloc(sizeof(char *) * (game->height + 1));
	if (!visited)
		return (false);
	i = 0;
	while (i < game->height)
	{
		visited[i] = ft_strdup(game->map[i]);
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (false);
		}
		i++;
	}
	visited[game->height] = NULL;
	flood_fill(visited, game->player_x, game->player_y, game);
	result = check_reachable(visited, game);
	i = 0;
	while (i < game->height)
		free(visited[i++]);
	free(visited);
	return (result);
}
