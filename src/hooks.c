/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42madrid.com    +#+  +:+       +#+        */
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

static void	rotate_L(t_cub *cub)
{
	cub->map.cam.oldDirX = cub->map.cam.dir_x;
	cub->map.cam.dir_x = cub->map.cam.dir_x * cos(-0.01) - cub->map.cam.dir_y * sin(-0.01);
	cub->map.cam.dir_y = cub->map.cam.oldDirX * sin(-0.01) + cub->map.cam.dir_y * cos(-0.01);
	cub->map.cam.oldPlaneX = cub->map.cam.plane_x;
	cub->map.cam.plane_x = cub->map.cam.plane_x * cos(-0.01) - cub->map.cam.plane_y * sin(-0.01);
	cub->map.cam.plane_y = cub->map.cam.oldPlaneX * sin(-0.01) + cub->map.cam.plane_y * cos(-0.01);
}

static void	rotate_R(t_cub *cub)
{
	cub->map.cam.oldDirX = cub->map.cam.dir_x;
	cub->map.cam.dir_x = cub->map.cam.dir_x * cos(0.01) - cub->map.cam.dir_y * sin(0.01);
	cub->map.cam.dir_y = cub->map.cam.oldDirX * sin(0.01) + cub->map.cam.dir_y * cos(0.01);
	cub->map.cam.oldPlaneX = cub->map.cam.plane_x;
	cub->map.cam.plane_x = cub->map.cam.plane_x * cos(0.01) - cub->map.cam.plane_y * sin(0.01);
	cub->map.cam.plane_y = cub->map.cam.oldPlaneX * sin(0.01) + cub->map.cam.plane_y * cos(0.01);
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
		rotate_L(cub);
	else if (keycode == ROTATE_RIGHT)
		rotate_R(cub);
}

int	ft_input_hook(int keycode, t_cub *cub)
{
	ft_printf("Key code: %i\n", keycode);
	if (keycode == ESCAPE)
		hook_exit(cub);
	ft_keyhooks(keycode, cub);
	return (0);
}