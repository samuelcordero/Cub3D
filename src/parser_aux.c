/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agserran <agserran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:38:46 by agserran          #+#    #+#             */
/*   Updated: 2024/02/20 15:15:56 by agserran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	copy_file(char *line, size_t size, int fd, char **res)
{
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

static void	copy_texture_path(char **path, char **file, int *row, int *ctr)
{
	*path = ft_strdup(file[*row] + 3);
	ft_delete_row(file, *row);
	++*ctr;
}

void	parse_texture(t_map *map, char **file, int *row, int *ctr)
{
	if (ft_strncmp(file[*row], "NO ", 3) == 0)
		copy_texture_path(&map->text_paths[NO], file, row, ctr);
	else if (ft_strncmp(file[*row], "SO ", 3) == 0)
		copy_texture_path(&map->text_paths[SO], file, row, ctr);
	else if (ft_strncmp(file[*row], "WE ", 3) == 0)
		copy_texture_path(&map->text_paths[WE], file, row, ctr);
	else if (ft_strncmp(file[*row], "EA ", 3) == 0)
		copy_texture_path(&map->text_paths[EA], file, row, ctr);
	else if (!ft_strncmp(file[*row], "C ", 2)
		|| !ft_strncmp(file[*row], "F ", 2))
	{
		if (!ft_strncmp(file[*row], "F ", 2))
			map->floor_color = ft_get_color(file[*row]);
		else
			map->ceiling_color = ft_get_color(file[*row]);
		ft_delete_row(file, *row);
		++*ctr;
	}
	else if (ft_strncmp(file[*row], "", 1) == 0)
		ft_delete_row(file, *row);
	else if (*ctr < 6 && ft_strncmp(file[*row], "", 1))
		ft_error_exit(INV_MAP_MSG, 1);
	else
		++*row;
}
