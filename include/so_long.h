/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:00:43 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/09 07:18:44 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	int			p_x;
	int			p_y;
	int			width;
	int			height;
	int			moves;
	int			x;
	int			y;
	int			collectibles_left;
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
}				t_data;

int				map_pce(t_data *game);
void			flood_fill(char **map, int x, int y);
char			**copy_map(char **map, int width, int height);
void			check_valid_path(t_data *game);
void			get_player_position(t_data *game);
void			check_map_walls(t_data *game);
void			init_window(t_data *game);
char			**load_map(char *filename, int *width, int *height);
void			free_map(char **map, int height);
void			render_map(t_data *game);
void			handle_input(mlx_key_data_t keydata, void *param);
void			get_new_position(mlx_key_data_t keydata, t_data *game,
					int *new_x, int *new_y);
void			move_player(t_data *game, int new_x, int new_y);
void			update_map_state(t_data *game, int new_x, int new_y);
mlx_image_t		*load_texture(t_data *game, char *path);
void			check_exit_condition(t_data *game);
void			validate_map_characters(t_data *game);
char			*read_map_file(char *filename);
void			count_pce(t_data *game, int *pce);
void			validate_map_file(char *filename);

#endif
