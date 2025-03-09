/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:04:56 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/09 09:36:20 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		return (ft_printf("Usage: %s <map_file.ber>\n", argv[0]), 1);
	validate_map_file(argv[1]);
	game.moves = 0;
	game.map = load_map(argv[1], &game.width, &game.height);
	if (!game.map || map_pce(&game) == -1)
		return (1);
	validate_map_characters(&game);
	check_map_walls(&game);
	get_player_position(&game);
	init_window(&game);
	render_map(&game);
	mlx_key_hook(game.mlx, &handle_input, &game);
	ft_printf("Game started! Press WASD to move.\n");
	mlx_loop(game.mlx);
	return (0);
}
