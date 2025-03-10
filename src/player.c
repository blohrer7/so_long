/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:24:24 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/10 09:16:27 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_window(t_data *game)
{
	game->mlx = mlx_init(game->width * 32, game->height * 32, "so_long", true);
	if (!game->mlx)
		exit(ft_printf("Error: MLX42 initialization failed\n"));
	game->wall = load_texture(game, "src/textures/wall.png");
	game->floor = load_texture(game, "src/textures/floor.png");
	game->player = load_texture(game, "src/textures/player.png");
	game->collectible = load_texture(game, "src/textures/collectible.png");
	game->exit = load_texture(game, "src/textures/exit.png");
}

mlx_image_t	*load_texture(t_data *game, char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(path);
	if (!tex)
		exit(ft_printf("Error: Failed to load texture: %s\n", path));
	img = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	return (img);
}

void	update_map_state(t_data *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->map[new_y][new_x] = '0';
		game->collectibles_left--;
		ft_printf("Collectible picked up! Remaining: %d\n",
			game->collectibles_left);
	}
	if (game->map[game->p_y][game->p_x] == 'E')
		mlx_image_to_window(game->mlx, game->exit, game->p_x * 32, game->p_y
			* 32);
	else
		mlx_image_to_window(game->mlx, game->floor, game->p_x * 32, game->p_y
			* 32);
}

void	check_exit_condition(t_data *game)
{
	if (game->map[game->p_y][game->p_x] == 'E')
	{
		if (game->collectibles_left == 0)
		{
			ft_printf("Congratulations! You have completed the game!\n");
			mlx_terminate(game->mlx);
			exit(0);
		}
		else
		{
			ft_printf("You must collect all items before exiting! Remaining:"
				"%d\n", game->collectibles_left);
		}
	}
}

void	clean_exit(t_data *game)
{
	if (!game)
		return ;
	free_map(game->map, game->height);
	mlx_delete_image(game->mlx, game->wall);
	mlx_delete_image(game->mlx, game->floor);
	mlx_delete_image(game->mlx, game->player);
	mlx_delete_image(game->mlx, game->collectible);
	mlx_delete_image(game->mlx, game->exit);
	mlx_terminate(game->mlx);
	ft_printf("Game exited successfully.\n");
	exit(0);
}
