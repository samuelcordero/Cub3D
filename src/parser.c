/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:40:55 by sacorder          #+#    #+#             */
/*   Updated: 2024/02/20 14:28:07 by agserran         ###   ########.fr       */
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
	copy_file(line, size, fd, res);
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

static int	ft_load_map(char **file, t_map *map)
{
	int	row;
	int	ctr;

	row = 0;
	ctr = 0;
	while (file[row])
		parse_texture(map, file, &row, &ctr);
	if (ctr != 6)
		ft_error_exit(NOT_ENOUGH_ATTR, 1);
	row = 0;
	while (file[row])
		++row;
	map->map_array = ft_calloc(row + 1, sizeof(char *));
	if (!map->map_array)
		ft_error_exit(MEM_ERR_MSG, 1);
	row = -1;
	while (file[++row])
		map->map_array[row] = ft_strdup(file[row]);
	return (0);
}

static void	ft_check_map(t_map *map)
{
	int	i;
	int	j;
	int	ctr;

	ctr = 0;
	if (!map->map_array || !map->text_paths[NO] || !map->text_paths[SO]
		|| !map->text_paths[WE] || !map->text_paths[EA]
		|| map->floor_color == -1
		|| map->ceiling_color == -1)
		ft_error_exit(INV_MAP_MSG, 1);
	i = -1;
	while (map->map_array[++i])
	{
		j = -1;
		map_runer(map, &i, &j, &ctr);
	}
	if (ctr != 1)
		ft_error_exit(INV_MAP_MSG, 1);
	ft_check_closed_map(map);
}

void	ft_parse_map(t_map *map, int argc, char **argv)
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
	ft_free_array(file);
	ft_check_map(map);
}
