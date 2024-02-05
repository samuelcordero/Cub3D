/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:19 by agserran          #+#    #+#             */
/*   Updated: 2024/02/05 16:24:01 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct s_raycast{
	int 	x;
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
}t_raycast;


#endif