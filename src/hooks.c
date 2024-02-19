/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:29:48 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/19 16:35:11 by agserran         ###   ########.fr       */
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
		move_forward(cub);
	else if (keycode == MOVE_BK)
		move_back(cub);
	else if (keycode == ROTATE_LEFT)
		rotate(cub, ROT_SP);
	else if (keycode == ROTATE_RIGHT)
		rotate(cub, -ROT_SP);
}

int	ft_mouse_hook(int x, int y, t_cub *cub)
{
	if (y != -1 && cub->prev_mouse_x > 0)
		rotate(cub, (float)(x - cub->prev_mouse_x) / (double)(WIN_WIDTH / 16));
	cub->prev_mouse_x = x;
	return (0);
}

int	ft_ignore_clicks(int button, int x, int y, t_cub *cub)
{
	(void)cub;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

int	ft_input_hook(int keycode, t_cub *cub)
{
	if (keycode == ESCAPE)
		hook_exit(cub);
	ft_keyhooks(keycode, cub);
	return (0);
}
