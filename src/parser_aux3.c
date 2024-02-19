/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:27:28 by agserran          #+#    #+#             */
/*   Updated: 2024/02/19 17:38:13 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	setter_n_s(t_map *map, int i, int j)
{
	map->cam.y = ((double)(i)) + 0.5;
	map->cam.x = ((double)(j)) + 0.5;
	if (map->map_array[i][j] == 'N')
	{
		map->cam.dir_x = 0;
		map->cam.dir_y = -1;
		map->cam.plane_x = 0.66;
		map->cam.plane_y = 0.00;
	}
	if (map->map_array[i][j] == 'S')
	{
		map->cam.dir_x = 0;
		map->cam.dir_y = 1;
		map->cam.plane_x = -0.66;
		map->cam.plane_y = 0.00;
	}
}

static void	setter_e_w(t_map *map, int i, int j)
{
	if (map->map_array[i][j] == 'E')
	{
		map->cam.dir_x = 1;
		map->cam.dir_y = 0;
		map->cam.plane_x = 0;
		map->cam.plane_y = 0.66;
	}
	if (map->map_array[i][j] == 'W')
	{
		map->cam.dir_x = -1;
		map->cam.dir_y = 0;
		map->cam.plane_x = 0;
		map->cam.plane_y = -0.66;
	}
}

void	map_runer(t_map *map, int *i, int *j, int *ctr)
{
	while (map->map_array[*i][++*j])
	{
		if (map->map_array[*i][*j] != ' ' &&
		!ft_strchr(VLID_CHARS, map->map_array[*i][*j]))
			ft_error_exit(INV_MAP_MSG, 1);
		if (ft_strchr(PLAYER_CHARS, map->map_array[*i][*j]))
		{
			setter_n_s(map, *i, *j);
			setter_e_w(map, *i, *j);
			map->map_array[*i][*j] = '0';
			++*ctr;
		}
	}
}
