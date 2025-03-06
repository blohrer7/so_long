/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:31:57 by blohrer           #+#    #+#             */
/*   Updated: 2025/03/06 11:33:04 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_pce(char **map)
{
	int	pce[3];
	int	i;
	int	j;

	i = 0;
	pce[0] = 0;
	pce[1] = 0;
	pce[2] = 0;
	while (map[i])
	{
		j = 0;
		while (j++, map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
				pce[0]++;
			if (map[i][j] == 'C')
				pce[1]++;
			if (map[i][j] == 'E')
				pce[2]++;
		}
		i++;
	}
	if (pce[0] != 1 || pce[1] < 1 || pce[2] != 1)
		return (-1);
	return (1);
}


char **read_map(const char *filename)
{

}
