/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:13:00 by sacorder          #+#    #+#             */
/*   Updated: 2023/11/13 19:26:51 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	raycast(t_cub *cub)
{
	int		x;
	int		hit;
    int		side;
	int		line_height;
	double	cameraX;
	double	perp_dist;
	double	side_dist[2];
	double	delta_dist[2];
	double	raydir[2];
	int		map_pos[2];
	int		step[2];
	int		line_start;
	int		line_end;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		cameraX = 2 * x / (double)WIN_WIDTH - 1;
		raydir[X] = cub->map.cam.dir_x + cub->map.cam.plane_x * cameraX;
		raydir[Y] = cub->map.cam.dir_y + cub->map.cam.plane_y * cameraX;
		map_pos[X] = (int)cub->map.cam.x;
		map_pos[Y] = (int)cub->map.cam.y;
		if (raydir[X] == 0)
			delta_dist[X] = 1e30;
		else
			delta_dist[X] = fabs(1 / raydir[X]);
		if (raydir[Y] == 0)
			delta_dist[Y] = 1e30;
		else
			delta_dist[Y] = fabs(1 / raydir[Y]);
		hit = 0;
		if(raydir[X] < 0)
		{
			step[X] = -1;
			side_dist[X] = (cub->map.cam.x - map_pos[X]) * delta_dist[X];
		}
		else
		{
			step[X] = 1;
			side_dist[X] = (map_pos[X] + 1.0 - cub->map.cam.x) * delta_dist[X];
		}
		if(raydir[Y] < 0)
		{
			step[Y] = -1;
			side_dist[Y] = (cub->map.cam.y - map_pos[Y]) * delta_dist[Y];
		}
		else
		{
			step[Y] = 1;
			side_dist[Y] = (map_pos[Y] + 1.0 - cub->map.cam.y) * delta_dist[Y];
		}
		while(hit == 0)
		{
			if (side_dist[X] < side_dist[Y])
			{
				side_dist[X] += delta_dist[X];
				map_pos[X] += step[X];
				side = 0;
			}
			else
			{
				side_dist[Y] += delta_dist[Y];
				map_pos[Y] += step[Y];
				side = 1;
			}
			if (cub->map.map_array[map_pos[Y]][map_pos[X]] == '1')
					hit = 1;
		}
		if (side)
			perp_dist = side_dist[Y] - delta_dist[Y];
		else
			perp_dist = side_dist[X] - delta_dist[X];
		line_height = (int)(WIN_HEIGHT / perp_dist);
		line_start = -line_height / 2 + WIN_HEIGHT / 2;
		line_end = line_height / 2 + WIN_HEIGHT / 2;
		if (line_start < 0)
			line_start = 0;
		if (line_end < 0)
			line_end = 0;
		img_ver_line(&cub->win_img, x, line_start, line_end, 0xffffff);
	}
	
}