/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:04:56 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/10 08:55:52 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	game;

	game.moves = 0;
	if (argc != 2)
		return (ft_printf("Usage: %s <map_file.ber>\n", argv[0]), 1);
	game.map = load_map(argv[1], &game.width, &game.height);
	if (!game.map)
		return (1);
	validate_map_characters(&game);
	if (map_pce(&game) == -1)
		return (ft_printf("Error: Invalid map (must contain 1P, at least 1C, and 1E)\n"), 1);
	check_map_walls(&game);
	get_player_position(&game);

	// ✅ NEU: Überprüft, ob alle Collectibles und das Exit erreichbar sind
	check_valid_path(&game);

	init_window(&game);
	mlx_resize_hook(game.mlx, handle_resize, &game);
	render_map(&game);
	mlx_key_hook(game.mlx, &handle_input, &game);
	ft_printf("✅ Game started! Press WASD to move.\n");
	mlx_loop(game.mlx);
	return (0);
}


// int	main(int argc, char **argv)
// {
// 	t_data	game;

// 	if (argc != 2)
// 		return (ft_printf("Usage: %s <map_file.ber>\n", argv[0]), 1);
// 	validate_map_file(argv[1]);
// 	game.moves = 0;
// 	game.map = load_map(argv[1], &game.width, &game.height);
// 	if (!game.map || map_pce(&game) == -1)
// 		return (1);
// 	validate_map_characters(&game);
// 	check_map_walls(&game);
// 	get_player_position(&game);
// 	init_window(&game);
// 	render_map(&game);
// 	mlx_key_hook(game.mlx, &handle_input, &game);
// 	ft_printf("Game started! Press WASD to move.\n");
// 	mlx_loop(game.mlx);
// 	return (0);
// }
