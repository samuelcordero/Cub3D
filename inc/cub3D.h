/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:07:15 by sacorder          #+#    #+#             */
/*   Updated: 2023/11/05 18:40:55 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdlib.h>
# include "libft.h"
# include "cub3D_defines.h"

//parser.c

void	ft_parse_map(t_map *map, int argc, char **argv);

//utils.c

void	ft_error_exit(char *msg, int exitcode);
void	ft_free_array(char **array);

#endif
