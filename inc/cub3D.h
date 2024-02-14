/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:07:15 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/14 15:02:54 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdlib.h>
# include "libft.h"
# include "mlx.h"
# include "cub3D_defines.h"
# include "raycast.h"

//draw.c

void	img_pix_put(t_img *img, int x, int y, int color);
void	img_ver_line(t_cub *cub, t_raycast *ray);
int		render(t_cub *cub);

//hooks.c

int		hook_exit(t_cub *cub);
int		ft_mouse_hook(int x, int y, t_cub *cub);
int		ft_input_hook(int keycode, t_cub *cub);

//parser.c

void	ft_parse_map(t_map *map, int argc, char **argv, t_cub *cub);

//raycaster.c

void	raycast(t_cub *cub, t_raycast *ray);

//textures.c

int		ft_load_textures(t_cub *cub);
void	ft_exit_text_err();
t_img	*get_texture(t_cub *cub, t_raycast *ray);
int		get_color_from_text(t_raycast *ray, int y, t_img *txtr);

//utils.c

void	ft_error_exit(char *msg, int exitcode);
void	ft_free_array(char **array);
void	rotate(t_cub *cub, float angle);

#endif
