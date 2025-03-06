/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:04:56 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/06 10:25:21 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
    {
        write(2, "Error\nUsage: ./so_long <map_file.ber>\n", 38);
        return (1);
    }

    data.map = read_map(argv[1]); // Function to load map from file
    if (!data.map)
    {
        write(2, "Error\nFailed to load map\n", 25);
        return (1);
    }

    get_map_size(&data, data.map); // Get width and height from map

    init_window(&data); // Initialize MLX window with correct size

    mlx_loop(data.mlx); // Start MLX42 loop

    return (0);
}

