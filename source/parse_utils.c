/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:46:55 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/19 11:09:11 by jkoupy           ###   ########.fr       */
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

void	set_player(t_map *map, int x, int y, char c)
{
	map->player.x = x;
	map->player.y = y;
	if (c == 'N')
		map->player.direction = 0;
	else if (c == 'E')
		map->player.direction = 90;
	else if (c == 'S')
		map->player.direction = 180;
	else if (c == 'W')
		map->player.direction = 270;
}
