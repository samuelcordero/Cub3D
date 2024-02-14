/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:26:50 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/14 15:03:34 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H
# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define X 0
# define Y 1
# define ROT_SPEED 0.05
# define SPEED 0.05

# ifndef MAC_OS
#  define ESCAPE 65307
#  define MOVE_FW 119
#  define MOVE_BK 115
#  define ROTATE_RIGHT 97
#  define ROTATE_LEFT 100
#  define ZOOM_OUT 120
#  define ZOOM_IN 122
#  define RESET_CAM 114
#  define CHANGE_PROJ 112
#  define V_INC 118
#  define V_DEC 98
#  define TOGGLE_HELP 104
# else
#  define ESCAPE 53
#  define MOVE_FW 13
#  define MOVE_BK 1
#  define ROTATE_RIGHT 0
#  define ROTATE_LEFT 2
#  define ZOOM_OUT 7
#  define ZOOM_IN 6
#  define RESET_CAM 15
#  define CHANGE_PROJ 35
#  define V_INC 9
#  define V_DEC 11
#  define TOGGLE_HELP 4
# endif


typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		heigth;
}	t_img;

typedef struct s_cam
{
	double	x;
	double	y;
	double	plane_x;
	double	plane_y;
	double	dir_x;
	double	dir_y;
	double	oldDirX;
	double	oldPlaneX;
}	t_cam;

typedef struct s_map
{
	t_cam	cam;	
	int		ceiling_color;
	int		floor_color;
	char	**map_array;
	int		rows;
	char	*text_paths[4];
}	t_map;

typedef struct s_cub
{
	t_map	map;
	void	*mlx;
	void	*win_ptr;
	t_img	win_img;
	t_img	textures[4];
	int		prev_mouse_x;
}	t_cub;

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