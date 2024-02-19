/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:25:02 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/19 17:58:28 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error_exit(char *msg, int exitcode)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(exitcode);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		exit(-1);
	while (array[i] != NULL)
	{
		free(array[i]);
		++i;
	}
	free(array);
}

void	rotate(t_cub *cub, double angle)
{
	cub->map.cam.olddirx = cub->map.cam.dir_x;
	cub->map.cam.dir_x = cub->map.cam.dir_x
		* cos(angle) - cub->map.cam.dir_y * sin(angle);
	cub->map.cam.dir_y = cub->map.cam.olddirx
		* sin(angle) + cub->map.cam.dir_y * cos(angle);
	cub->map.cam.oldplanex = cub->map.cam.plane_x;
	cub->map.cam.plane_x = cub->map.cam.plane_x
		* cos(angle) - cub->map.cam.plane_y * sin(angle);
	cub->map.cam.plane_y = cub->map.cam.oldplanex
		* sin(angle) + cub->map.cam.plane_y * cos(angle);
}
