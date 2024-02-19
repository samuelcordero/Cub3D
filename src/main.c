/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:11:52 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/19 17:50:29 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.mlx = mlx_init();
	if (!cub.mlx)
		exit(1);
	ft_parse_map(&cub.map, argc, argv);
	if (ft_load_textures(&cub))
		ft_exit_text_err();
	cub.win_ptr = mlx_new_window(cub.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!cub.win_ptr)
		exit(1);
	cub.win_img.mlx_img = mlx_new_image(cub.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub.win_img.mlx_img)
		exit(1);
	cub.win_img.addr = mlx_get_data_addr(cub.win_img.mlx_img, &cub.win_img.bpp,
			&cub.win_img.line_len, &cub.win_img.endian);
	mlx_loop_hook(cub.mlx, &render, &cub);
	mlx_hook(cub.win_ptr, 17, 0, &hook_exit, &cub);
	mlx_hook(cub.win_ptr, 2, 1, &ft_input_hook, &cub);
	mlx_hook(cub.win_ptr, 6, 1L << 6, ft_mouse_hook, &cub);
	mlx_mouse_hook(cub.win_ptr, &ft_ignore_clicks, &cub);
	mlx_loop(cub.mlx);
	free(cub.mlx);
	return (0);
}
