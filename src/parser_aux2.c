/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:14:07 by agserran          #+#    #+#             */
/*   Updated: 2024/02/19 17:34:43 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_top_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->map_array[0][++i])
	{
		if (map->map_array[0][i] != '1' && map->map_array[0][i] != ' ')
			ft_error_exit(INV_MAP_MSG, 1);
	}
}

void	ft_check_bottom_map(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->map_array[j + 1])
		++j;
	i = -1;
	while (map->map_array[j][++i])
	{
		if (map->map_array[j][i] != '1' && map->map_array[j][i] != ' ')
			ft_error_exit(INV_MAP_MSG, 1);
	}
}

static void	closed_aux(t_map *map, int *i, int *j)
{
	if (map->map_array[*i][*j] == '0' &&
	(!ft_strchr(VLID_CHARS, map->map_array[*i][*j + 1])
	|| !ft_strchr(VLID_CHARS, map->map_array[*i + 1][*j]) ||
	!ft_strchr(VLID_CHARS, map->map_array[*i][*j - 1])
		|| !ft_strchr(VLID_CHARS, map->map_array[*i - 1][*j])))
		ft_error_exit(INV_MAP_MSG, 1);
	if (ft_strchr(PLAYER_CHARS, map->map_array[*i][*j]) &&
	(!ft_strchr(VLID_CHARS, map->map_array[*i][*j + 1])
	|| !ft_strchr(VLID_CHARS, map->map_array[*i + 1][*j]) ||
	!ft_strchr(VLID_CHARS, map->map_array[*i][*j - 1]) ||
	!ft_strchr(VLID_CHARS, map->map_array[*i - 1][*j])))
		ft_error_exit(INV_MAP_MSG, 1);
}

void	ft_check_closed_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	ft_check_top_map(map);
	ft_check_bottom_map(map);
	while (map->map_array[++i + 1])
	{
		j = 0 ;
		if (map->map_array[i][0] != '1' ||
		*(ft_strchr(map->map_array[i], '\0') - 1) != '1')
			ft_error_exit(INV_MAP_MSG, 1);
		while (map->map_array[i][++j + 1])
		{
			closed_aux(map, &i, &j);
		}
	}
}
