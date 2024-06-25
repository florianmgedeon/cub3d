/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:46:55 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/25 14:02:00 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

void	set_player(t_player *player, int x, int y, char c)
{
	player->x = x;
	player->y = y;
	if (c == 'N')
		player->direction = 0;
	else if (c == 'E')
		player->direction = 90;
	else if (c == 'S')
		player->direction = 180;
	else if (c == 'W')
		player->direction = 270;
}

bool	arg_check(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Error\nWrong number of arguments\n", 32);
		return (false);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		write(2, "Error\nWrong file extension\n", 28);
		return (false);
	}
	return (true);
}

bool	map_check(t_map *map)
{
	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
		|| map->size_x == 0 || map->size_y == 0 || !map->data
		|| map->player.x == 0 || map->player.y == 0)
	{
		write(2, "Error\nMap is not well formated\n", 31);
		if (!map->no_path)
			write(2, "NO texture is missing\n", 22);
		if (!map->so_path)
			write(2, "SO texture is missing\n", 22);
		if (!map->we_path)
			write(2, "WE texture is missing\n", 22);
		if (!map->ea_path)
			write(2, "EA texture is missing\n", 22);
		if (map->size_x == 0 || map->size_y == 0)
			write(2, "Map size is missing\n", 21);
		if (!map->data)
			write(2, "Map data is missing\n", 21);
		if (map->player.x == 0 || map->player.y == 0)
			write(2, "Player is missing\n", 19);
		return (false);
	}	
	return (true);
}
