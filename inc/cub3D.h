/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:07:15 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/20 13:25:43 by agserran         ###   ########.fr       */
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
int		ft_ignore_clicks(int button, int x, int y, t_cub *cub);
int		ft_input_hook(int keycode, t_cub *cub);

//parser.c

void	ft_parse_map(t_map *map, int argc, char **argv);

//raycaster.c

void	raycast(t_cub *cub, t_raycast *ray);

//textures.c

int		ft_load_textures(t_cub *cub);
void	ft_exit_text_err(void);
t_img	*get_texture(t_cub *cub, t_raycast *ray);
int		get_color_from_text(t_raycast *ray, int y, t_img *txtr);

//utils.c

void	ft_error_exit(char *msg, int exitcode);
void	ft_free_array(char **array);
void	rotate(t_cub *cub, double angle);

//hooks_aux.c

void	move_forward(t_cub *cub);
void	move_back(t_cub *cub);
void	move_left(t_cub *cub);
void	move_right(t_cub *cub);

//parser_aux.c

void	copy_file(char *line, size_t size, int fd, char **res);
void	parse_texture(t_map *map, char **file, int *row, int *ctr);

//parser_aux2.c

void	ft_check_top_map(t_map *map);
void	ft_check_bottom_map(t_map *map);
void	ft_check_closed_map(t_map *map);

//parser_aux3.c

void	map_runer(t_map *map, int *i, int *j, int *ctr);

#endif
