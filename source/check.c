/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:08:44 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/27 13:48:35 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	map_check(t_map map)
{
	if (!null_check(map))
		return (false);
	if (!color_check(map))
		return (false);
	if (!player_check(map.player))
		return (false);
	if (!valid_map_check(map))
		return (false);
	return (true);
}

//null check
bool	null_check(t_map map)
{
	if (!map.no_path || !map.so_path || !map.we_path || !map.ea_path
		|| map.size_x == 0 || map.size_y == 0 || !map.data
		|| map.player.x == 0 || map.player.y == 0
		|| *map.no_path == '\0' || *map.so_path == '\0'
		|| *map.we_path == '\0' || *map.ea_path == '\0')
	{
		write(2, "Error\nMap is not well formated\n", 31);
		if (!map.no_path || *map.no_path == '\0')
			write(2, "NO texture is missing\n", 22);
		if (!map.so_path || *map.so_path == '\0')
			write(2, "SO texture is missing\n", 22);
		if (!map.we_path || *map.we_path == '\0')
			write(2, "WE texture is missing\n", 22);
		if (!map.ea_path || *map.ea_path == '\0')
			write(2, "EA texture is missing\n", 22);
		if (map.size_x == 0 || map.size_y == 0)
			write(2, "Map size is missing\n", 21);
		if (!map.data)
			write(2, "Map data is missing\n", 21);
		if (map.player.x == 0 || map.player.y == 0)
			write(2, "Player is missing\n", 19);
		return (false);
	}
	return (true);
}

//color check
bool	color_check(t_map map)
{
	t_color	ceiling;
	t_color	floor;

	ceiling = map.ceiling;
	floor = map.floor;
	if (floor.r == -1 || floor.g == -1 || floor.b == -1
		|| ceiling.r == -1 || ceiling.g == -1 || ceiling.b == -1
		|| floor.r > 255 || floor.g > 255 || floor.b > 255
		|| ceiling.r > 255 || ceiling.g > 255 || ceiling.b > 255)
	{
		write(2, "Error\nMap is not well formated\n", 31);
		if (floor.r <= -1 || floor.g <= -1 || floor.b <= -1
			|| floor.r > 255 || floor.g > 255 || floor.b > 255)
			write(2, "Floor color is missing/incorrect\n", 33);
		if (ceiling.r <= -1 || ceiling.g <= -1 || ceiling.b <= -1
			|| ceiling.r > 255 || ceiling.g > 255 || ceiling.b > 255)
			write(2, "Ceiling color is missing/incorrect\n", 35);
		return (false);
	}
	return (true);
}

//player check
bool	player_check(t_player player)
{
	if (player.direction == -1 || player.x == -1 || player.y == -1)
	{
		write(2, "Error\nPlayer is missing\n", 24);
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
			if (map.data[y][x] == 0 || map.data[y][x] == 2)
			{
				if (y == 0 || y == map.size_y - 1
					|| x == 0 || x == map.size_x - 1
					|| map.data[y - 1][x] == -1 || map.data[y + 1][x] == -1
					|| map.data[y][x - 1] == -1 || map.data[y][x + 1] == -1)
				{
					write(2, "Error\nMap is not closed\n", 25);
					return (true);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}
