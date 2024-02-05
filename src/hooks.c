/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:29:48 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/05 16:52:05 by sacorder         ###   ########.fr       */
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
		cub->map.cam.x += cub->map.cam.dir_x * 0.1;
		cub->map.cam.y += cub->map.cam.dir_y * 0.1;
	}
	else if (keycode == MOVE_BK)
	{
		cub->map.cam.x -= cub->map.cam.dir_x * 0.1;
		cub->map.cam.y -= cub->map.cam.dir_y * 0.1;
	}
	else if (keycode == MOVE_LEFT)
	{
		cub->map.cam.x += cub->map.cam.dir_x * 0.1;
		cub->map.cam.y -= cub->map.cam.dir_y * 0.1;
	}
	else if (keycode == MOVE_RIGHT)
	{
		cub->map.cam.x -= cub->map.cam.dir_x * 0.1;
		cub->map.cam.y += cub->map.cam.dir_y * 0.1;
	}
	else if (keycode == ROTATE_LEFT)
	{
		cub->map.cam.oldDirX = cub->map.cam.dir_x;
		cub->map.cam.dir_x = cub->map.cam.dir_x * cos(-0.01) - cub->map.cam.dir_y * sin(-0.01);
		cub->map.cam.dir_y = cub->map.cam.oldDirX * sin(-0.01) + cub->map.cam.dir_y * cos(-0.01);
		cub->map.cam.oldPlaneX = cub->map.cam.plane_x;
		cub->map.cam.plane_x = cub->map.cam.plane_x * cos(-0.01) - cub->map.cam.plane_y * sin(-0.01);
		cub->map.cam.plane_y = cub->map.cam.oldPlaneX * sin(-0.01) + cub->map.cam.plane_y * cos(-0.01);
	}
	else if (keycode == ROTATE_RIGHT)
	{
		cub->map.cam.oldDirX = cub->map.cam.dir_x;
		cub->map.cam.dir_x = cub->map.cam.dir_x * cos(0.01) - cub->map.cam.dir_y * sin(0.01);
		cub->map.cam.dir_y = cub->map.cam.oldDirX * sin(0.01) + cub->map.cam.dir_y * cos(0.01);
		cub->map.cam.oldPlaneX = cub->map.cam.plane_x;
		cub->map.cam.plane_x = cub->map.cam.plane_x * cos(0.01) - cub->map.cam.plane_y * sin(0.01);
		cub->map.cam.plane_y = cub->map.cam.oldPlaneX * sin(0.01) + cub->map.cam.plane_y * cos(0.01);
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