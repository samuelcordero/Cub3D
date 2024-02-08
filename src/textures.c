/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:32:21 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/08 14:03:51 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_load_textures(t_cub *cub)
{
	cub->textures[NO].mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_paths[NO], NULL, NULL);
	cub->textures[SO].mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_paths[SO], NULL, NULL);
	cub->textures[EA].mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_paths[EA], NULL, NULL);
	cub->textures[WE].mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_paths[WE], NULL, NULL);
	if (!cub->textures[NO].mlx_img || !cub->textures[SO].mlx_img || !cub->textures[WE].mlx_img || !cub->textures[EA].mlx_img)
		return (1);
	cub->textures[NO].addr =  mlx_get_data_addr(cub->textures[NO].mlx_img, &cub->textures[NO].bpp, &cub->textures[NO].line_len, &cub->textures[NO].endian);
	cub->textures[SO].addr =  mlx_get_data_addr(cub->textures[SO].mlx_img, &cub->textures[SO].bpp, &cub->textures[SO].line_len, &cub->textures[SO].endian);
	cub->textures[EA].addr =  mlx_get_data_addr(cub->textures[EA].mlx_img, &cub->textures[EA].bpp, &cub->textures[EA].line_len, &cub->textures[EA].endian);
	cub->textures[WE].addr =  mlx_get_data_addr(cub->textures[WE].mlx_img, &cub->textures[WE].bpp, &cub->textures[WE].line_len, &cub->textures[WE].endian);
	if (!cub->textures[NO].addr || !cub->textures[SO].addr || !cub->textures[WE].addr || !cub->textures[EA].addr)
		return (1);
	return (0);
}

void	ft_exit_text_err()
{
	ft_putendl_fd("Error: couldn't load textures images", STDERR_FILENO);
	exit(1);
}
