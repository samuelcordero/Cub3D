/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:32:21 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/13 22:58:50 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_load_textures(t_cub *cub)
{
	cub->textures[NO].mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_paths[NO], &cub->textures[NO].width, &cub->textures[NO].heigth);
	cub->textures[SO].mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_paths[SO], &cub->textures[SO].width, &cub->textures[SO].heigth);
	cub->textures[EA].mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_paths[EA], &cub->textures[EA].width, &cub->textures[EA].heigth);
	cub->textures[WE].mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_paths[WE], &cub->textures[WE].width, &cub->textures[WE].heigth);
	if (!cub->textures[NO].mlx_img || !cub->textures[SO].mlx_img || !cub->textures[WE].mlx_img || !cub->textures[EA].mlx_img)
		return (1);
	cub->textures[NO].addr = mlx_get_data_addr(cub->textures[NO].mlx_img, &cub->textures[NO].bpp, &cub->textures[NO].line_len, &cub->textures[NO].endian);
	cub->textures[SO].addr = mlx_get_data_addr(cub->textures[SO].mlx_img, &cub->textures[SO].bpp, &cub->textures[SO].line_len, &cub->textures[SO].endian);
	cub->textures[EA].addr = mlx_get_data_addr(cub->textures[EA].mlx_img, &cub->textures[EA].bpp, &cub->textures[EA].line_len, &cub->textures[EA].endian);
	cub->textures[WE].addr = mlx_get_data_addr(cub->textures[WE].mlx_img, &cub->textures[WE].bpp, &cub->textures[WE].line_len, &cub->textures[WE].endian);
	if (!cub->textures[NO].addr || !cub->textures[SO].addr || !cub->textures[WE].addr || !cub->textures[EA].addr)
		return (1);
	return (0);
}

void	ft_exit_text_err()
{
	ft_putendl_fd("Error: couldn't load textures images", STDERR_FILENO);
	exit(1);
}

/*
	para las texturas:
		discriminar NO o SO / WE o EA
			con side (0 es NO o SO, 1 es WE o EA)
		discriminar entre las dos restantes:
			con ray->raydir[X] y ray->raydir[Y] (vector unitario que marca la dirección de la cámara)
			si side es 0, con raydir[Y], si side es 1 con raydir[X]
			si son negativos; SO o EA, si son positivos, NO o WE
	luego para calcular las texturas;
		con la parte entera de la componente x o y (discriminando como antes) de vector (posicion + rayo)

*/

t_img	*get_texture(t_cub *cub, t_raycast *ray)
{
	if (ray->side)
	{
		if (ray->raydir[Y] > 0)
			return (&cub->textures[SO]);
		return (&cub->textures[NO]);
	}
	if (ray->raydir[X] > 0)
		return (&cub->textures[EA]);
	return (&cub->textures[WE]);
}

int		get_color_from_text(t_cub *cub, t_raycast *ray, int y, t_img *txtr)
{
	unsigned int	color;
	int				h;
	int				x;
	double			rel_x;
	
	color = 0;
	h = ((double)(y - ray->line_start) / (double)(ray->line_end - ray->line_start)) * (txtr->heigth - 1);
	if (ray->side)
		rel_x = cub->map.cam.x + ray->side_dist[X];
	else
		rel_x = cub->map.cam.y + ray->side_dist[Y];
	if (rel_x < 0)
		rel_x *= -1;
	rel_x -= (int)rel_x;
	x = rel_x * txtr->width;
	color = *(unsigned int *)(txtr->addr + (h * txtr->line_len + x * (txtr->bpp / 8)));
	return (color);
}
