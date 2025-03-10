/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:31:57 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/10 09:16:52 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_pce(t_data *game, int *pce)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
				pce[0]++;
			else if (game->map[i][j] == 'C')
				pce[1]++;
			else if (game->map[i][j] == 'E')
				pce[2]++;
			j++;
		}
		i++;
	}
}

int	map_pce(t_data *game)
{
	int	pce[3];

	pce[0] = 0;
	pce[1] = 0;
	pce[2] = 0;
	count_pce(game, pce);
	game->collectibles_left = pce[1];
	if (pce[0] != 1 || pce[1] < 1 || pce[2] != 1)
		return (ft_printf("Error: Invalid map (1P, 1E, at "
				"least 1C required)\n"), -1);
	ft_printf("Collectibles in map: %d\n", game->collectibles_left);
	return (1);
}

void	check_map_walls(t_data *game)
{
	int	i;

	i = 0;
	if (!game->map || !game->map[0])
		exit(ft_printf("Error: Invalid map structure!\n"));
	while (i < game->width)
	{
		if (game->map[0][i] != '1' || game->map[game->height - 1][i] != '1')
			exit(ft_printf("Error: Map is not enclosed by walls!\n"));
		i++;
	}
	i = 0;
	while (i < game->height)
	{
		if (!game->map[i] || game->map[i][0] != '1' || game->map[i][game->width
			- 1] != '1')
			exit(ft_printf("Error: Map is not enclosed by walls!\n"));
		i++;
	}
}

char	**allocate_map_copy(int width, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * height);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = malloc(sizeof(char) * (width + 1));
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

char	**copy_map(char **map, int width, int height)
{
	char	**copy;
	int		i;
	int		j;

	copy = allocate_map_copy(width, height);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			copy[i][j] = map[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
	return (copy);
}
