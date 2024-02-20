/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:32:21 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/19 17:55:33 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_load_textures(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		cub->textures[i].mlx_img = mlx_xpm_file_to_image(cub->mlx,
				cub->map.text_paths[i], &cub->textures[i].width,
				&cub->textures[i].heigth);
	}
	if (!cub->textures[NO].mlx_img || !cub->textures[SO].mlx_img
		|| !cub->textures[WE].mlx_img || !cub->textures[EA].mlx_img)
		return (1);
	i = -1;
	while (++i < 4)
		cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].mlx_img,
				&cub->textures[i].bpp, &cub->textures[i].line_len,
				&cub->textures[i].endian);
	if (!cub->textures[NO].addr || !cub->textures[SO].addr
		|| !cub->textures[WE].addr || !cub->textures[EA].addr)
		return (1);
	return (0);
}

void	ft_exit_text_err(void)
{
	ft_putendl_fd("Error: couldn't load textures images", STDERR_FILENO);
	exit(1);
}

t_img	*get_texture(t_cub *cub, t_raycast *ray)
{
	if (ray->side)
	{
		if (ray->raydir[Y] > 0)
			return (&cub->textures[NO]);
		return (&cub->textures[SO]);
	}
	if (ray->raydir[X] > 0)
		return (&cub->textures[WE]);
	return (&cub->textures[EA]);
}

int	get_color_from_text(t_raycast *ray, int y, t_img *txtr)
{
	unsigned int	color;
	int				h;

	color = 0;
	h = ((double)(y - ray->line_start)
			/ (double)(ray->line_end - ray->line_start)) * (txtr->heigth - 1);
	color = *(unsigned int *)(txtr->addr
			+ (h * txtr->line_len + ray->txtr_x * (txtr->bpp / 8)));
	return (color);
}
