/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:04:56 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/09 07:18:16 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		return (ft_printf("Usage: %s <map_file.ber>\n", argv[0]), 1);
	validate_map_file(argv[1]); // ✅ Check if the file has a .ber extension
	game.moves = 0;
	game.map = load_map(argv[1], &game.width, &game.height);
	if (!game.map || map_pce(&game) == -1)
		return (ft_printf("Error: Invalid map (must contain 1P, at least 1C,"
				"and 1E)\n"), 1);
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

// int main(int argc, char **argv)
// {
//     t_data game;

//     game.moves = 0;
//     // ✅ Step 1: Check if the map file is provided
//     if (argc != 2)
//     {
//         ft_printf("Usage: %s <map_file.ber>\n", argv[0]);
//         return (1);
//     }

//         // ✅ Step 1: Load the map
//     game.map = load_map(argv[1], &game.width, &game.height);
//     if (!game.map)
//         return (1);

//     // ✅ Step 2: Validate characters in the map
//     validate_map_characters(&game);

//     // ✅ Step 3: Validate P, C, and E count
//     if (map_pce(&game) == -1)
//     {
//         ft_printf("Error: Invalid map (must contain 1P, at least 1C,
// 	and 1E)\n");
// //         return (1);
// //     }

// //     // ✅ Step 4: Check if the map is surrounded by walls
// //     check_map_walls(&game);

// //     // ✅ Step 5: Find player position
// //     get_player_position(&game);

// //     // ✅ Step 3: Find the player starting position
// //     get_player_position(&game);

// //     // ✅ Step 3: Initialize MLX42 and load textures
// //     init_window(&game);

// //     // ✅ Step 4: Render the map with all textures
// //     render_map(&game);

// //     // ✅ Step 5: Register the key input function
// //     // ✅ Step 5: Register key input function
// //     mlx_key_hook(game.mlx, &handle_input, &game);

// //     ft_printf("✅ Game started! Press WASD to move.\n");

// //     // ✅ Step 6: Start MLX42 event loop
// //     mlx_loop(game.mlx);

// //     return (0);
// // }
