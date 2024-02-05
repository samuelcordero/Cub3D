/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:29:48 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/05 17:30:16 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	hook_exit(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win_ptr);
	exit(0);
	return (0);
}

void	ft_keyhooks(int keycode, t_cub *cub)
{
	if (keycode == MOVE_FW)
	{
		if (cub->map.map_array[(int)(cub->map.cam.x + cub->map.cam.dir_x * SPEED)][(int)cub->map.cam.y] != '1')
			cub->map.cam.x += cub->map.cam.dir_x * SPEED;
		if (cub->map.map_array[(int)cub->map.cam.x][(int)(cub->map.cam.y + cub->map.cam.dir_y * SPEED)] != '1')
			cub->map.cam.y += cub->map.cam.dir_y * SPEED;
	}
	else if (keycode == MOVE_BK)
	{
		if (cub->map.map_array[(int)(cub->map.cam.x - cub->map.cam.dir_x * SPEED)][(int)cub->map.cam.y] != '1' && (int)(cub->map.cam.x + cub->map.cam.dir_x * SPEED) >= 0)
			cub->map.cam.x -= cub->map.cam.dir_x * SPEED;
		if (cub->map.map_array[(int)cub->map.cam.x][(int)(cub->map.cam.y - cub->map.cam.dir_y * SPEED)] != '1' && (int)(cub->map.cam.y + cub->map.cam.dir_y * SPEED) >= 0)
			cub->map.cam.y -= cub->map.cam.dir_y * SPEED;
	}
	else if (keycode == ROTATE_LEFT)
	{
		cub->map.cam.oldDirX = cub->map.cam.dir_x;
		cub->map.cam.dir_x = cub->map.cam.dir_x * cos(-ROT_SPEED) - cub->map.cam.dir_y * sin(-ROT_SPEED);
		cub->map.cam.dir_y = cub->map.cam.oldDirX * sin(-ROT_SPEED) + cub->map.cam.dir_y * cos(-ROT_SPEED);
		cub->map.cam.oldPlaneX = cub->map.cam.plane_x;
		cub->map.cam.plane_x = cub->map.cam.plane_x * cos(-ROT_SPEED) - cub->map.cam.plane_y * sin(-ROT_SPEED);
		cub->map.cam.plane_y = cub->map.cam.oldPlaneX * sin(-ROT_SPEED) + cub->map.cam.plane_y * cos(-ROT_SPEED);
	}
	else if (keycode == ROTATE_RIGHT)
	{
		cub->map.cam.oldDirX = cub->map.cam.dir_x;
		cub->map.cam.dir_x = cub->map.cam.dir_x * cos(ROT_SPEED) - cub->map.cam.dir_y * sin(ROT_SPEED);
		cub->map.cam.dir_y = cub->map.cam.oldDirX * sin(ROT_SPEED) + cub->map.cam.dir_y * cos(ROT_SPEED);
		cub->map.cam.oldPlaneX = cub->map.cam.plane_x;
		cub->map.cam.plane_x = cub->map.cam.plane_x * cos(ROT_SPEED) - cub->map.cam.plane_y * sin(ROT_SPEED);
		cub->map.cam.plane_y = cub->map.cam.oldPlaneX * sin(ROT_SPEED) + cub->map.cam.plane_y * cos(0.01);
	}
}

int	ft_input_hook(int keycode, t_cub *cub)
{
	ft_printf("Key code: %i\n", keycode);
	if (keycode == ESCAPE)
		hook_exit(cub);
	ft_keyhooks(keycode, cub);
	return (0);
}