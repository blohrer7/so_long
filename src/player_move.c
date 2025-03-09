/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 08:47:17 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/09 08:10:34 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_player_position(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'P')
			{
				game->p_x = x;
				game->p_y = y;
				ft_printf("Player found at: (%d, %d)\n", game->p_x, game->p_y);
				return ;
			}
			x++;
		}
		y++;
	}
	ft_printf("Error: No player found in map!\n");
	exit(1);
}

void	move_player(t_data *game, int new_x, int new_y)
{
	game->p_x = new_x;
	game->p_y = new_y;
	mlx_image_to_window(game->mlx, game->player, new_x * 32, new_y * 32);
}

void	get_new_position(mlx_key_data_t keydata, t_data *game, int *new_x,
		int *new_y)
{
	*new_x = game->p_x;
	*new_y = game->p_y;
	if (keydata.key == MLX_KEY_W)
		(*new_y)--;
	if (keydata.key == MLX_KEY_S)
		(*new_y)++;
	if (keydata.key == MLX_KEY_A)
		(*new_x)--;
	if (keydata.key == MLX_KEY_D)
		(*new_x)++;
}

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_data	*game;
	int		new_x;
	int		new_y;

	game = (t_data *)param;
	if (!game || !game->map || keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(game->mlx);
		exit(0);
	}
	if (keydata.key != MLX_KEY_W && keydata.key != MLX_KEY_A
		&& keydata.key != MLX_KEY_S && keydata.key != MLX_KEY_D)
		return ;
	get_new_position(keydata, game, &new_x, &new_y);
	if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height)
		return ;
	if (game->map[new_y][new_x] == '1')
		return ;
	update_map_state(game, new_x, new_y);
	move_player(game, new_x, new_y);
	game->moves++;
	ft_printf("🚶 Move #%d\n", game->moves);
	check_exit_condition(game);
}
