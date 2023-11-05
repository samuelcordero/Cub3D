/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:25:02 by sacorder          #+#    #+#             */
/*   Updated: 2023/11/05 18:40:19 by sacorder         ###   ########.fr       */
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
