/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:19 by agserran          #+#    #+#             */
/*   Updated: 2024/02/14 02:04:55 by sacorder         ###   ########.fr       */
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
}	t_raycast;


#endif