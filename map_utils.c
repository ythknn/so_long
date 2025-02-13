/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihakan <yihakan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:28:06 by yihakan           #+#    #+#             */
/*   Updated: 2025/02/13 16:41:05 by yihakan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_walls(t_game *game)
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
			return (0);
		if (game->map[row][0] != '1' || game->map[row][game->width - 1] != '1')
			return (0);
		row++;
	}
	col = 0;
	while (col < game->width)
	{
		if (game->map[0][col] != '1' || game->map[game->height - 1][col] != '1')
			return (0);
		col++;
	}
	return (1);
}

int	count_map_elements(t_game *game, int *p_count, int *e_count,
		int *c_count)
{
	int		row;
	int		col;

	row = -1;
	while (++row < game->height)
	{
		col = -1;
		while (++col < game->width)
		{
			if (game->map[row][col] == 'P')
			{
				(*p_count)++;
				game->player_x = col;
				game->player_y = row;
			}
			else if (game->map[row][col] == 'E')
				(*e_count)++;
			else if (game->map[row][col] == 'C')
				(*c_count)++;
			else if (game->map[row][col] != '0' && game->map[row][col] != '1')
				return (0);
		}
	}
	return (1);
}

void	flood_fill(char **visited, int x, int y, t_game *game)
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

int	check_reachable(char **visited, t_game *game)
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

int	init_visited_map(t_game *game, char ***visited)
{
	int	i;

	*visited = malloc(sizeof(char *) * (game->height + 1));
	if (!*visited)
		return (0);
	i = 0;
	while (i < game->height)
	{
		(*visited)[i] = ft_strdup(game->map[i]);
		if (!(*visited)[i])
		{
			while (--i >= 0)
				free((*visited)[i]);
			free(*visited);
			return (0);
		}
		i++;
	}
	(*visited)[game->height] = NULL;
	return (1);
}
