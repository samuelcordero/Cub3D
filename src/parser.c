/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:40:55 by sacorder          #+#    #+#             */
/*   Updated: 2023/11/05 18:52:26 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	**ft_load_file(char *filename)
{
	char	**res;
	int		size;
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
		res[++size] = line;
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

static int	ft_load_map(char **file, t_map *map)
{
	int	row;
	int	flag;

	row = -1;
	flag = 6;
	while(file[++row] && flag)
	{
		if (ft_strncmp(file[row], "NO", 3) == 0)
			map->text_paths[NO] = ft_strdup(file[row]);
		else if (ft_strncmp(file[row], "SO", 3) == 0)
			map->text_paths[SO] = ft_strdup(file[row]);
		else if (ft_strncmp(file[row], "WE", 3) == 0)
			map->text_paths[WE] = ft_strdup(file[row]);
		else if (ft_strncmp(file[row], "EA", 3) == 0)
			map->text_paths[EA] = ft_strdup(file[row]);
		else if (ft_strncmp(file[row], "C", 2) == 0)
			map->ceiling_color = ft_get_color(file[row]);
		else if (ft_strncmp(file[row], "F", 2) == 0)
			map->text_paths[EA] = ft_get_color(file[row]);
	}
}

void	ft_parse_map(t_map *map, int argc, char **argv)
{
	char	**file;
	(void)map;
	
	if (argc != 2 || ft_check_filename(argv[1]))
		ft_error_exit(ARG_NBR_MSG, 1);
	ft_printf("map is %s\n", argv[1]);
	file = ft_load_file(argv[1]);
	if (ft_load_map(file, map))
		ft_error_exit(INV_MAP_MSG, 1);
	ft_free_array(file);
	
}