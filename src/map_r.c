/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:16:09 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/07 18:21:29 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void render_map(t_data *game)
{
    int x, y;

    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            // ✅ Step 1: Draw the floor first (background)
            mlx_image_to_window(game->mlx, game->floor, x * 32, y * 32);

            // ✅ Step 2: Draw all other objects EXCEPT the player
            if (game->map[y][x] == '1')
                mlx_image_to_window(game->mlx, game->wall, x * 32, y * 32);
            if (game->map[y][x] == 'C')
                mlx_image_to_window(game->mlx, game->collectible, x * 32, y * 32);
            if (game->map[y][x] == 'E')
                mlx_image_to_window(game->mlx, game->exit, x * 32, y * 32);

            x++;
        }
        y++;
    }

    // ✅ Step 3: Draw the player LAST so it's on top
    mlx_image_to_window(game->mlx, game->player, game->p_x * 32, game->p_y * 32);
}


