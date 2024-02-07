/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:53:26 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/07 23:55:36 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	img_ver_line(t_img *img, int x, int y1, int y2, int color)
{
	int	y;

	y = y1 - 1;
	if (y < 0)
		y = 0;
	while (++y < y2 && y < WIN_HEIGHT)
		img_pix_put(img, x, y, color);
}

static void	render_horizon(t_cub *cub)
{
	int	i;
	int	j;
	int	win_half;

	i = -1;
	win_half = WIN_HEIGHT / 2;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
		{
			if (i < win_half)
				img_pix_put(&cub->win_img, j, i, cub->map.ceiling_color);
			else
				img_pix_put(&cub->win_img, j, i, cub->map.floor_color);
		}
			
	}
}

int	render(t_cub *cub)
{
	t_raycast ray;

	printf("Debug:\nPos: (%f, %f)\nDir: (%f, %f)\nPlane: (%f, %f)\n", cub->map.cam.x, cub->map.cam.y, cub->map.cam.dir_x, cub->map.cam.dir_y, cub->map.cam.plane_x, cub->map.cam.plane_y);
	render_horizon(cub);
	raycast(cub, &ray);
	mlx_put_image_to_window(cub->mlx, cub->win_ptr,
			cub->win_img.mlx_img, 0, 0);
	return (0);
}
