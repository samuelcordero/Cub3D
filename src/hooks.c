/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:29:48 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/08 14:04:45 by sacorder         ###   ########.fr       */
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
		if (cub->map.map_array[(int)cub->map.cam.y][(int)(cub->map.cam.x + cub->map.cam.dir_x * SPEED)] != '1'
			&& cub->map.map_array[(int)cub->map.cam.y][(int)(cub->map.cam.x + cub->map.cam.dir_x * SPEED)])
			cub->map.cam.x += cub->map.cam.dir_x * SPEED;
		if (cub->map.map_array[(int)(cub->map.cam.y + cub->map.cam.dir_y * SPEED)][(int)cub->map.cam.x] != '1'
			&& cub->map.map_array[(int)(cub->map.cam.y + cub->map.cam.dir_y * SPEED)][(int)cub->map.cam.x])
			cub->map.cam.y += cub->map.cam.dir_y * SPEED;
	}
	else if (keycode == MOVE_BK)
	{
		if (cub->map.map_array[(int)cub->map.cam.y][(int)(cub->map.cam.x - cub->map.cam.dir_x * SPEED)] != '1' && (int)(cub->map.cam.x + cub->map.cam.dir_x * SPEED) >= 0
			&& cub->map.map_array[(int)cub->map.cam.y][(int)(cub->map.cam.x - cub->map.cam.dir_x * SPEED)])
			cub->map.cam.x -= cub->map.cam.dir_x * SPEED;
		if (cub->map.map_array[(int)(cub->map.cam.y - cub->map.cam.dir_y * SPEED)][(int)cub->map.cam.x] != '1' && (int)(cub->map.cam.y + cub->map.cam.dir_y * SPEED) >= 0
			&& cub->map.map_array[(int)(cub->map.cam.y - cub->map.cam.dir_y * SPEED)][(int)cub->map.cam.x])
			cub->map.cam.y -= cub->map.cam.dir_y * SPEED;
	}
	else if (keycode == ROTATE_LEFT)
		rotate(cub, ROT_SPEED);
	else if (keycode == ROTATE_RIGHT)
		rotate(cub, -ROT_SPEED);
}

int	ft_input_hook(int keycode, t_cub *cub)
{
	ft_printf("Key code: %i\n", keycode);
	if (keycode == ESCAPE)
		hook_exit(cub);
	ft_keyhooks(keycode, cub);
	return (0);
}