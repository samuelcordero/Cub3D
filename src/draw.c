/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:53:26 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/10 18:58:42 by sacorder         ###   ########.fr       */
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

void	img_ver_line(t_cub *cub, t_raycast *ray)
{
	int		y;
	t_img	*txtr;

	y = ray->line_start - 1;
	if (y < 0)
		y = 0;
	txtr = get_texture(cub, ray);
	while (++y < ray->line_end && y < WIN_HEIGHT)
		img_pix_put(&cub->win_img, ray->x, y, get_color_from_text(cub, ray, y, txtr));
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

	//printf("Debug:\nPos: (%f, %f)\nDir: (%f, %f)\nPlane: (%f, %f)\n", cub->map.cam.x, cub->map.cam.y, cub->map.cam.dir_x, cub->map.cam.dir_y, cub->map.cam.plane_x, cub->map.cam.plane_y);
	render_horizon(cub);
	raycast(cub, &ray);
	mlx_put_image_to_window(cub->mlx, cub->win_ptr,
			cub->win_img.mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win_ptr,
			cub->textures[0].mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win_ptr,
			cub->textures[1].mlx_img, 128, 0);
	mlx_put_image_to_window(cub->mlx, cub->win_ptr,
			cub->textures[2].mlx_img, 256, 0);
	mlx_put_image_to_window(cub->mlx, cub->win_ptr,
			cub->textures[3].mlx_img, 384, 0);
	return (0);
}
