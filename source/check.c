/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:08:44 by jkoupy            #+#    #+#             */
/*   Updated: 2024/07/04 21:58:33 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//main check function
bool	map_check(t_map map)
{
	if (!null_check(map))
		return (false);
	if (!color_check(map))
		return (false);
	if (!valid_map_check(map))
		return (false);
	if (!texture_check(map))
		return (false);
	return (true);
}

//null check, if a part of the map was not set
bool	null_check(t_map map)
{
	int	error;

	error = 0;
	if (!map.no_path || *map.no_path == '\0')
		error = write(2, "Error\nNO texture is missing\n", 28);
	if (!map.so_path || *map.so_path == '\0')
		error = write(2, "Error\nSO texture is missing\n", 28);
	if (!map.we_path || *map.we_path == '\0')
		error = write(2, "Error\nWE texture is missing\n", 28);
	if (!map.ea_path || *map.ea_path == '\0')
		error = write(2, "Error\nEA texture is missing\n", 28);
	if (!map.data || map.size_x == 0 || map.size_y == 0)
		error = write(2, "Error\nMap data is missing\n", 27);
	if (map.player.x == -1 || map.player.y == -1
		|| map.player.dir_x == -2 || map.player.dir_y == -2)
		error = write(2, "Error\nPlayer is missing\n", 24);
	if (map.floor.r == -1 || map.floor.g == -1 || map.floor.b == -1)
		error = write(2, "Error\nFloor color is missing\n", 29);
	if (map.ceiling.r == -1 || map.ceiling.g == -1 || map.ceiling.b == -1)
		error = write(2, "Error\nCeiling color is missing\n", 31);
	if (error)
		return (false);
	return (true);
}

//color check, checks range 0-255
bool	color_check(t_map map)
{
	t_color	ceiling;
	t_color	floor;

	ceiling = map.ceiling;
	floor = map.floor;
	if (floor.r < 0 || floor.g < 0 || floor.b < 0
		|| ceiling.r < 0 || ceiling.g < 0 || ceiling.b < 0
		|| floor.r > 255 || floor.g > 255 || floor.b > 255
		|| ceiling.r > 255 || ceiling.g > 255 || ceiling.b > 255)
	{
		write(2, "Error\nMap is not well formated\n", 31);
		if (floor.r < 0 || floor.g < 0 || floor.b < 0
			|| floor.r > 255 || floor.g > 255 || floor.b > 255)
			write(2, "Floor color is incorrect\n", 25);
		if (ceiling.r < 0 || ceiling.g < 0 || ceiling.b < 0
			|| ceiling.r > 255 || ceiling.g > 255 || ceiling.b > 255)
			write(2, "Ceiling color is incorrect\n", 27);
		return (false);
	}
	return (true);
}

//valid map check
//there is no 0 next to -1 or the wall
bool	valid_map_check(t_map map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map.size_y)
	{
		x = 0;
		while (x < map.size_x && map.data[y][x] != -2)
		{
			if (map.data[y][x] == 0)
			{
				if (!is_closed(map, x, y))
				{
					write(2, "Error\nMap is not closed\n", 25);
					return (false);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	is_closed(t_map map, int x, int y)
{
	if (x == 0 || y == 0 || x == map.size_x - 1 || y == map.size_y - 1)
		return (false);
	if (x + 1 > row_length(map.data[y]) || map.data[y][x + 1] < 0)
		return (false);
	if (x - 1 < 0 || map.data[y][x - 1] < 0)
		return (false);
	if (row_length(map.data[y + 1]) < x || map.data[y + 1][x] < 0)
		return (false);
	if (row_length(map.data[y - 1]) < x || map.data[y - 1][x] < 0)
		return (false);
	return (true);
}
