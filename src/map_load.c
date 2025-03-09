/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:16:09 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/09 09:12:50 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			mlx_image_to_window(game->mlx, game->floor, x * 32, y * 32);
			if (game->map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->wall, x * 32, y * 32);
			if (game->map[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->collectible, x * 32, y
					* 32);
			if (game->map[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->exit, x * 32, y * 32);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->player, game->p_x * 32, game->p_y
		* 32);
}

char	*read_map_file(char *filename)
{
	static char	buffer[10000];
	int			fd;
	int			bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error: Could not open file\n"), NULL);
	bytes_read = read(fd, buffer, 9999);
	close(fd);
	if (bytes_read <= 0)
		return (ft_printf("Error: Could not read file\n"), NULL);
	if (bytes_read == 9999)
		return (ft_printf("Error: Map file is too large!\n"), NULL);
	buffer[bytes_read] = '\0';
	return (buffer);
}

char	**load_map(char *filename, int *width, int *height)
{
	char	*file_content;
	char	**map;
	int		i;

	file_content = read_map_file(filename);
	i = 0;
	if (!file_content)
		return (NULL);
	map = ft_split(file_content, '\n');
	if (!map)
		return (ft_printf("Error: Memory allocation failed\n"), NULL);
	*height = 0;
	while (map[*height])
		(*height)++;
	*width = (int)ft_strlen(map[0]);
	while (++i < *height)
		if ((int)ft_strlen(map[i]) != *width)
			return (ft_printf("Error: Map is not rectangular\n"), NULL);
	return (map);
}

void	validate_map_characters(t_data *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] != '0' && game->map[y][x] != '1'
				&& game->map[y][x] != 'P' && game->map[y][x] != 'C'
				&& game->map[y][x] != 'E')
			{
				ft_printf("Error: Invalid character '%c' found in map!\n",
					game->map[y][x]);
				exit(1);
			}
			x++;
		}
		y++;
	}
}
