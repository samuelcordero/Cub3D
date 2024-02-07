/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:40:55 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/07 12:27:10 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	**ft_load_file(char *filename)
{
	char	**res;
	size_t	size;
	int		fd;
	char	*line;

	size = 0;
	fd = open(filename, O_RDONLY, 0644);
	if (fd < -1)
		ft_error_exit(FILE_ERR_MSG, 1);
	line = get_next_line(fd);
	while (line)
	{
		size++;
		free(line);
		line = get_next_line(fd);
	}
	res = ft_calloc(size + 1, sizeof(char *));
	if (!res)
		ft_error_exit(MEM_ERR_MSG, 1);
	close(fd);
	fd = open(filename, O_RDONLY, 0644);
	if (fd < -1)
		ft_error_exit(FILE_ERR_MSG, 1);
	line = get_next_line(fd);
	size = -1;
	while (line)
	{
		res[++size] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (res);
}

static int	ft_check_filename(char *filename)
{
	char	*ext;
	
	ext = ft_strchr(filename, '.');
	if (!ext)
		return (1);
	if (ext == filename || ft_strncmp(ext, ".cub", 5))
		return (1);
	return (0);
}

static void	ft_delete_row(char **mat, int row)
{
	char	*tmp;

	tmp = mat[row];
	while (mat[row])
	{	
		mat[row] = mat[row + 1];
		++row;
	}
	if (tmp)
		free(tmp);
}

static int	ft_get_color(char *str)
{
	char	**splited;
	int		color;
	int		i;

	color = 0;
	str += 2;
	i = -1;
	while (str[++i])
		if (str[i] != ',' && !ft_isdigit(str[i]))
			ft_error_exit(INV_CLR_MSG, 1);
	splited = ft_split(str, ',');
	if (!splited[0] || !splited[1] || !splited[2] || splited[3])
		ft_error_exit(INV_MAP_MSG, 1);
	color += (ft_atoi(splited[0]) & 0xFF) << 16;
	color += (ft_atoi(splited[1]) & 0xFF) << 8;
	color += (ft_atoi(splited[2]) & 0xFF);
	ft_free_array(splited);
	return (color);
}


static int	ft_load_map(char **file, t_map *map)
{
	int	row;
	int	ctr;

	row = 0;
	ctr = 0;
	while(file[row])
	{
		if (ft_strncmp(file[row], "NO ", 3) == 0)
		{
			map->text_paths[NO] = ft_strdup(file[row]);
			ft_delete_row(file, row);
			++ctr;
		}
		else if (ft_strncmp(file[row], "SO ", 3) == 0)
		{
			map->text_paths[SO] = ft_strdup(file[row]);
			ft_delete_row(file, row);
			++ctr;
		}
		else if (ft_strncmp(file[row], "WE ", 3) == 0)
		{
			map->text_paths[WE] = ft_strdup(file[row]);
			ft_delete_row(file, row);
			++ctr;
		}
		else if (ft_strncmp(file[row], "EA ", 3) == 0)
		{
			map->text_paths[EA] = ft_strdup(file[row]);
			ft_delete_row(file, row);
			++ctr;
		}
		else if (ft_strncmp(file[row], "C ", 2) == 0)
		{
			map->ceiling_color = ft_get_color(file[row]);
			ft_delete_row(file, row);
			++ctr;
		}
		else if (ft_strncmp(file[row], "F ", 2) == 0)
		{
			map->floor_color = ft_get_color(file[row]);
			ft_delete_row(file, row);
			++ctr;
		}
		else if (ft_strncmp(file[row], "", 1) == 0)
			ft_delete_row(file, row);
		else
			++row;
	}
	if (ctr != 6)
		ft_error_exit(NOT_ENOUGH_ATTR, 1);
	row = 0;
	while(file[row])
		++row;
	map->map_array = ft_calloc(row + 1, sizeof(char *));
	if (!map->map_array)
		ft_error_exit(MEM_ERR_MSG, 1);
	row = -1;
	while(file[++row])
		map->map_array[row] = ft_strdup(file[row]);
	return (0);
}

static void	ft_check_top_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->map_array[0][++i])
	{
		if (map->map_array[0][i] != '1' && map->map_array[0][i] != ' ')
			ft_error_exit(INV_MAP_MSG, 1);
	}
}

static void	ft_check_bottom_map(t_map *map)
{
	int	i;
	int	j;
	
	j = 0;
	while (map->map_array[j + 1])
		++j;
	i = -1;
	while (map->map_array[j][++i])
	{
		if (map->map_array[j][i] != '1' && map->map_array[j][i] != ' ')
			ft_error_exit(INV_MAP_MSG, 1);
	}
}

static void	ft_check_closed_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	ft_check_top_map(map);
	ft_check_bottom_map(map);
	while (map->map_array[++i + 1])
	{
		j = 0 ;
		if (map->map_array[i][0] != '1' || *(ft_strchr(map->map_array[i], '\0') - 1) != '1')
			ft_error_exit(INV_MAP_MSG, 1);
		while (map->map_array[i][++j + 1])
		{
			if (map->map_array[i][j] == '0' && (!ft_strchr(VLID_CHARS, map->map_array[i][j + 1])
			|| !ft_strchr(VLID_CHARS, map->map_array[i + 1][j]) || !ft_strchr(VLID_CHARS, map->map_array[i][j - 1])
				|| !ft_strchr(VLID_CHARS, map->map_array[i - 1][j])))
				ft_error_exit(INV_MAP_MSG, 1);
			if (ft_strchr(PLAYER_CHARS, map->map_array[i][j]) && (!ft_strchr(VLID_CHARS, map->map_array[i][j + 1])
			|| !ft_strchr(VLID_CHARS, map->map_array[i + 1][j]) || !ft_strchr(VLID_CHARS, map->map_array[i][j - 1])
				|| !ft_strchr(VLID_CHARS, map->map_array[i - 1][j])))
				ft_error_exit(INV_MAP_MSG, 1);
		}
	}
}

static void	ft_check_map(t_map *map, t_cub *cub)
{
	int	i;
	int	j;
	int	ctr;

	ctr = 0;
	if (!map->map_array || !map->text_paths[NO] || !map->text_paths[SO]
		|| !map->text_paths[WE] || !map->text_paths[EA] || map->floor_color == -1
			|| map->ceiling_color == -1)
		ft_error_exit(INV_MAP_MSG, 1);
	i = -1;
	while (map->map_array[++i])
	{
		j = -1;
		while (map->map_array[i][++j])
		{
			if (map->map_array[i][j] != ' ' && !ft_strchr(VLID_CHARS, map->map_array[i][j]))
				ft_error_exit(INV_MAP_MSG, 1);
			if (ft_strchr(PLAYER_CHARS, map->map_array[i][j]))
			{
				map->cam.y = ((double) (i)) + 0.5;
				map->cam.x = ((double) (j)) + 0.5;
				if (map->map_array[i][j] == 'N')
				{
					map->cam.dir_x = 0;
					map->cam.dir_y = -1;
					map->cam.plane_x = 0.66;
					map->cam.plane_y = 0.00;
				}
				if (map->map_array[i][j] == 'S')
				{
					map->cam.dir_x = 0;
					map->cam.dir_y = 1;
					map->cam.plane_x = -0.66;
					map->cam.plane_y = 0.00;
				}
				if (map->map_array[i][j] == 'E')
				{
					map->cam.dir_x = 1;
					map->cam.dir_y = 0;
					map->cam.plane_x = 0;
					map->cam.plane_y = 0.66;
				}
				if (map->map_array[i][j] == 'W')
				{
					map->cam.dir_x = -1;
					map->cam.dir_y = 0;
					map->cam.plane_x = 0;
					map->cam.plane_y = -0.66;
				}
				(void) cub;
				map->map_array[i][j] = '0';
				++ctr;
			}
		}
	}
	if (ctr != 1)
			ft_error_exit(INV_MAP_MSG, 1);
	ft_check_closed_map(map);
}

void	ft_parse_map(t_map *map, int argc, char **argv, t_cub *cub)
{
	char	**file;
	
	ft_memset(map->text_paths, 0, sizeof(char *) * 4);
	map->ceiling_color = -1;
	map->floor_color = -1;
	if (argc != 2 || ft_check_filename(argv[1]))
		ft_error_exit(ARG_NBR_MSG, 1);
	file = ft_load_file(argv[1]);
	if (ft_load_map(file, map))
		ft_error_exit(INV_MAP_MSG, 1);
	/*int i = -1;
	while (map->map_array[++i])
		ft_printf("%s\n", map->map_array[i]);
	ft_printf("Colors : ceiling: %i, floor: %i \n", map->ceiling_color, map->floor_color);
	ft_printf("Textures paths : NO: %s \nSO: %s \nWE: %s \nEA: %s \n", map->text_paths[NO], map->text_paths[SO], map->text_paths[WE] ,map->text_paths[EA]); */
	ft_free_array(file);
	ft_check_map(map, cub);
}