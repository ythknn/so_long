/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihakan <yihakan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:28:10 by yihakan           #+#    #+#             */
/*   Updated: 2025/02/25 14:46:16 by yihakan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_height(const char *filename)
{
	int		fd;
	int		height;
	char	buffer[2];
	int		read_bytes;

	height = 1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, 1);
		if (read_bytes > 0 && buffer[0] == '\n')
			height++;
	}
	if (read_bytes == 0 && height == 0)
		height = 1;
	close(fd);
	return (height);
}

static int	check_line_width(char **map, int i, int width)
{
	if (i == 0)
		return (1);
	if (ft_strlen_int(map[i]) != width)
		return (0);
	return (1);
}

static void	clean_newline(char *line)
{
	int	len;

	len = ft_strlen_int(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	
}

static int	process_map_lines(int fd, char **map, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	while (i < game->height)
	{
		line = get_next_line(fd);
		if (!line)
			return (map[i] = NULL, 0);
		clean_newline(line);
		map[i] = line;
		if (i == 0)
			game->width = ft_strlen(map[0]);
		i++;
	}
	map[i] = NULL;
	i = 0;
	while (i < game->height)
	{
		if (!check_line_width(map, i, game->width))
			return (0);
		i++;
	}
	return (1);
}

char	**parse_map(const char *filename, t_game *game)
{
	int		fd;
	char	**map;

	game->height = get_height(filename);
	if (game->height <= 0)
	{
		write(1, "Permission denied\n", 18);
		return (NULL);
	}
	map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	if (!process_map_lines(fd, map, game))
	{
		free_map(map, game->height);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}
