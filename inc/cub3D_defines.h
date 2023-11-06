/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:26:50 by sacorder          #+#    #+#             */
/*   Updated: 2023/11/06 14:05:11 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct s_map
{
	int		ceiling_color;
	int		floor_color;
	char	**map_array;
	int		rows;
	char	*text_paths[4];
}	t_map;

//ERROR MESSAGES
# define ARG_NBR_MSG "Error\nInvalid args, arg should be ONE .cub map"
# define FILE_ERR_MSG "Error\nCouldn't open file"
# define MEM_ERR_MSG "Error\nCouldn't allocate memory"
# define INV_MAP_MSG "Error\nInvalid map file"
# define INV_CLR_MSG "Error\nInvalid map colors"
# define NOT_ENOUGH_ATTR "Error\nInvalid map attributes"
# define VLID_CHARS "01NSEW"
# define PLAYER_CHARS "NSEW"
# define NO 0
# define SO 1
# define WE 2
# define EA 3

#endif