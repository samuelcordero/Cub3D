/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:14:07 by agserran          #+#    #+#             */
/*   Updated: 2024/02/20 16:07:20 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_check_surroundings(t_map *map, int x, int y)
{
	if (x == 0 || y == 0 || !map->map_array[y + 1] || !map->map_array[y][x + 1]
		|| (map->map_array[y][x + 1] != '1' && map->map_array[y][x + 1] != '2')
		|| (map->map_array[y][x - 1] != '1' && map->map_array[y][x - 1] != '2'))
		ft_error_exit(INV_MAP_MSG, 1);
	if (!map->map_array[y - 1] || x >= (int)ft_strlen(map->map_array[y - 1])
		|| (map->map_array[y - 1][x] != '1' && map->map_array[y - 1][x] != '2'))
		ft_error_exit(INV_MAP_MSG, 1);
	if (!map->map_array[y + 1] || x >= (int)ft_strlen(map->map_array[y + 1])
		|| (map->map_array[y + 1][x] != '1' && map->map_array[y + 1][x] != '2'))
		ft_error_exit(INV_MAP_MSG, 1);
}

static void	ft_fill_reachable(t_map *map, int x, int y)
{
	if (y >= 0 && map->map_array[y])
		if (x < (int)ft_strlen(map->map_array[y])
			&& map->map_array[y][x] && map->map_array[y][x] == '0')
		{
			map->map_array[y][x] = '2';
			ft_fill_reachable(map, x + 1, y);
			ft_fill_reachable(map, x - 1, y);
			ft_fill_reachable(map, x, y + 1);
			ft_fill_reachable(map, x, y - 1);
		}
}

void	ft_check_closed_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	map->map_array[(int)map->cam.y][(int)map->cam.x] = '0';
	ft_fill_reachable(map, (int)map->cam.x, (int)map->cam.y);
	while (map->map_array[++i])
	{
		j = -1;
		while (map->map_array[i][++j])
		{
			if (map->map_array[i][j] == '2')
				ft_check_surroundings(map, j, i);
		}
	}
}
