/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:31:57 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/07 18:31:45 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_pce(t_data *game)
{
	int	pce[3];

	int i, j;
	i = 0;
	pce[0] = 0;
	pce[1] = 0;
	pce[2] = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'P')
				pce[0]++;
			if (game->map[i][j] == 'C')
				pce[1]++;
			if (game->map[i][j] == 'E')
				pce[2]++;
			j++;
		}
		i++;
	}
	game->collectible_left = pce[1];
	if (pce[0] != 1 || pce[1] < 1 || pce[2] != 1)
		return (-1);
	ft_printf("✅ Collectibles in map: %d\n", game->collectible_left);
	return (1);
}

void	check_map_walls(t_data *game)
{
	int	i;

	i = 0;
	while (i < game->width)
	{
		if (game->map[0][i] != '1' || game->map[game->height - 1][i] != '1')
		{
			ft_printf("Error: Map is not enclosed by walls\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < game->height)
	{
		if (game->map[i][0] != '1' || game->map[i][game->width - 1] != '1')
		{
			ft_printf("Error: Map is not enclosed by walls\n");
			exit(1);
		}
		i++;
	}
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

char	**copy_map(char **map, int width, int height)
{
	char	**copy;
	int		i;
	int		j;

	if (!(copy = malloc(sizeof(char *) * height)))
		return (NULL);
	i = 0;
	while (i < height)
	{
		if (!(copy[i] = malloc(sizeof(char) * (width + 1))))
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		j = -1;
		while (++j < width)
			copy[i][j] = map[i][j];
		copy[i][j] = '\0';
		i++;
	}
	return (copy);
}

void	check_valid_path(t_data *game)
{
	char	**temp_map;
	int		y;
	int		x;

	temp_map = copy_map(game->map, game->width, game->height);
	y = 0;
	if (!temp_map)
		exit(ft_printf("Error: Memory allocation failed\n"));
	flood_fill(temp_map, game->p_x, game->p_y);
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (temp_map[y][x] == 'C' || temp_map[y][x] == 'E')
			{
				free_map(temp_map, game->height);
				exit(ft_printf("Error: Not all collectibles or exit are reachable!\n"));
			}
			x++;
		}
		y++;
	}
	free_map(temp_map, game->height);
}

char	**load_map(char *filename, int *width, int *height)
{
	int		fd;
	int		bytes_read;
	char	buffer[BUFFER_SIZE + 1];
	char	**map;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error: Could not open file\n"), NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	close(fd);
	if (bytes_read <= 0)
		return (ft_printf("Error: Could not read file\n"), NULL);
	buffer[bytes_read] = '\0';
	*height = 0;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			(*height)++;
		i++;
	}
	map = ft_split(buffer, '\n');
	if (!map)
		return (ft_printf("Error: Memory allocation failed\n"), NULL);
	*width = ft_strlen(map[0]);
	i = 1;
	while (i < *height)
	{
		if ((int)ft_strlen(map[i]) != *width)
			return (ft_printf("Error: Map is not rectangular\n"), NULL);
		i++;
	}
	return (map);
}
void	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
