/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:31:27 by agserran          #+#    #+#             */
/*   Updated: 2024/02/20 13:31:43 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_cub *cub)
{
	if (cub->map.map_array[(int)cub->map.cam.y]
		[(int)(cub->map.cam.x + cub->map.cam.dir_x * SP)] != '1'
			&& cub->map.map_array[(int)cub->map.cam.y]
			[(int)(cub->map.cam.x + cub->map.cam.dir_x * SP)])
		cub->map.cam.x += cub->map.cam.dir_x * SP;
	if (cub->map.map_array[(int)(cub->map.cam.y + cub->map.cam.dir_y * SP)]
		[(int)cub->map.cam.x] != '1'
		&& cub->map.map_array[(int)(cub->map.cam.y +
		cub->map.cam.dir_y * SP)]
		[(int)cub->map.cam.x])
		cub->map.cam.y += cub->map.cam.dir_y * SP;
}

void	move_back(t_cub *cub)
{
	if (cub->map.map_array[(int)cub->map.cam.y]
		[(int)(cub->map.cam.x - cub->map.cam.dir_x * SP)] !=
		'1' && (int)(cub->map.cam.x + cub->map.cam.dir_x * SP) >= 0
		&& cub->map.map_array[(int)cub->map.cam.y]
		[(int)(cub->map.cam.x - cub->map.cam.dir_x * SP)])
		cub->map.cam.x -= cub->map.cam.dir_x * SP;
	if (cub->map.map_array[(int)(cub->map.cam.y - cub->map.cam.dir_y * SP)]
		[(int)cub->map.cam.x] !=
		'1' && (int)(cub->map.cam.y + cub->map.cam.dir_y * SP) >= 0
		&& cub->map.map_array[(int)(cub->map.cam.y -
		cub->map.cam.dir_y * SP)]
		[(int)cub->map.cam.x])
		cub->map.cam.y -= cub->map.cam.dir_y * SP;
}

void	move_right(t_cub *cub)
{
	if (cub->map.map_array[(int)cub->map.cam.y]
		[(int)(cub->map.cam.x + (-cub->map.cam.dir_y * SP))] != '1'
			&& cub->map.map_array[(int)cub->map.cam.y]
			[(int)(cub->map.cam.x + (-cub->map.cam.dir_y * SP))])
		cub->map.cam.x += (-cub->map.cam.dir_y * SP);
	if (cub->map.map_array[(int)(cub->map.cam.y + cub->map.cam.dir_x * SP)]
		[(int)cub->map.cam.x] != '1'
		&& cub->map.map_array[(int)(cub->map.cam.y +
		cub->map.cam.dir_x * SP)]
		[(int)cub->map.cam.x])
		cub->map.cam.y += cub->map.cam.dir_x * SP;
}

void	move_left(t_cub *cub)
{
	if (cub->map.map_array[(int)cub->map.cam.y]
		[(int)(cub->map.cam.x + cub->map.cam.dir_y * SP)] != '1'
			&& cub->map.map_array[(int)cub->map.cam.y]
			[(int)(cub->map.cam.x + cub->map.cam.dir_y * SP)])
		cub->map.cam.x += cub->map.cam.dir_y * SP;
	if (cub->map.map_array[(int)(cub->map.cam.y + (-cub->map.cam.dir_x * SP))]
		[(int)cub->map.cam.x] != '1'
		&& cub->map.map_array[(int)(cub->map.cam.y +
		(-cub->map.cam.dir_x * SP))]
		[(int)cub->map.cam.x])
		cub->map.cam.y += (-cub->map.cam.dir_x * SP);
}
