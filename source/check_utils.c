/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:32:22 by jkoupy            #+#    #+#             */
/*   Updated: 2024/07/04 21:34:12 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	texture_check(t_map map)
{
	if (!check_path(map.no_path))
		return (false);
	if (!check_path(map.so_path))
		return (false);
	if (!check_path(map.we_path))
		return (false);
	if (!check_path(map.ea_path))
		return (false);
	return (true);
}

bool	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nTexture path is incorrect\n", 32);
		return (false);
	}
	if (close(fd) == -1)
	{
		perror("Error\nClose");
		return (false);
	}
	return (true);
}

int	row_length(int *row)
{
	int	i;

	i = 0;
	while (row[i] != -2)
		i++;
	return (i);
}
