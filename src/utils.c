/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:49:25 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/12 12:06:47 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
				exit(ft_printf("Error: Not all collectibles or"
						"exit are reachable!\n"));
			}
			x++;
		}
		y++;
	}
	free_map(temp_map, game->height);
}

void	validate_map_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".ber", 4) != 0)
	{
		ft_printf("Error: Only .ber maps are allowed!\n");
		exit(1);
	}
}
