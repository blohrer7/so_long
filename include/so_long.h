/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:00:43 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/05 11:35:52 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define WIDTH 100
#define HEIGHT 100

typedef struct s_data
{
	void	*mlx;
	char	**map;
	int		p_x;
	int		p_y;
	int		width;
	int		height;
	int		moves;
}	t_data;

#endif
