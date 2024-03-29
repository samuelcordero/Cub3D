/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:13:00 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/20 14:31:36 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	void	init(t_cub *cub, t_raycast *ray)
{
	ray->camerax = 2 * ray->x / (double)WIN_WIDTH - 1;
	ray->raydir[X] = cub->map.cam.dir_x + cub->map.cam.plane_x * ray->camerax;
	ray->raydir[Y] = cub->map.cam.dir_y + cub->map.cam.plane_y * ray->camerax;
	ray->map_pos[X] = (int)cub->map.cam.x;
	ray->map_pos[Y] = (int)cub->map.cam.y;
}

static void	colision_detector(t_cub *cub, t_raycast *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			ray->map_pos[X] += ray->step[X];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			ray->map_pos[Y] += ray->step[Y];
			ray->side = 1;
		}
		if (cub->map.map_array[ray->map_pos[Y]][ray->map_pos[X]] == '1')
			ray->hit = 1;
	}
}

static void	init_side_step(t_cub *cub, t_raycast *ray)
{
	if (ray->raydir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_dist[X] = (cub->map.cam.x - ray->map_pos[X])
			* ray->delta_dist[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_dist[X] = (ray->map_pos[X] + 1.0 - cub->map.cam.x)
			* ray->delta_dist[X];
	}
	if (ray->raydir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_dist[Y] = (cub->map.cam.y - ray->map_pos[Y])
			* ray->delta_dist[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_dist[Y] = (ray->map_pos[Y] + 1.0 - cub->map.cam.y)
			* ray->delta_dist[Y];
	}
}

static void	init_delta(t_raycast *ray)
{
	if (ray->raydir[X] == 0)
		ray->delta_dist[X] = 1e30;
	else
		ray->delta_dist[X] = fabs(1 / ray->raydir[X]);
	if (ray->raydir[Y] == 0)
		ray->delta_dist[Y] = 1e30;
	else
		ray->delta_dist[Y] = fabs(1 / ray->raydir[Y]);
	ray->hit = 0;
}

void	raycast(t_cub *cub, t_raycast *ray)
{
	ray->x = -1;
	while (++ray->x < WIN_WIDTH)
	{
		init(cub, ray);
		init_delta(ray);
		init_side_step(cub, ray);
		colision_detector(cub, ray);
		if (ray->side)
			ray->perp_dist = ray->side_dist[Y] - ray->delta_dist[Y];
		else
			ray->perp_dist = ray->side_dist[X] - ray->delta_dist[X];
		ray->line_height = (int)(WIN_HEIGHT / ray->perp_dist);
		ray->line_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
		ray->line_end = ray->line_height / 2 + WIN_HEIGHT / 2;
		if (ray->line_end < 0)
			ray->line_end = 0;
		img_ver_line(cub, ray);
	}
}
