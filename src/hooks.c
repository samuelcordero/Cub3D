/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:29:48 by sacorder          #+#    #+#             */
/*   Updated: 2023/11/13 19:49:05 by sacorder         ###   ########.fr       */
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
	if (keycode == MOVE_UP)
		cub->map.cam.x -= 0.1;
	else if (keycode == MOVE_DOWN)
		cub->map.cam.x += 0.1;
	else if (keycode == MOVE_LEFT)
		cub->map.cam.y -= 0.1;
	else if (keycode == MOVE_RIGHT)
		cub->map.cam.y += 0.1;
	else if (keycode == ROTATE_LEFT)
	{
		cub->map.cam.dir_x = -1;
		cub->map.cam.dir_y = 0;
	}
	else if (keycode == ROTATE_RIGHT)
	{
		cub->map.cam.dir_x = 1;
		cub->map.cam.dir_y = 0;
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