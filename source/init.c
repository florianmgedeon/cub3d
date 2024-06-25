/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:30:08 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/25 14:19:05 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	data->map.no_path = NULL;
	data->map.so_path = NULL;
	data->map.we_path = NULL;
	data->map.ea_path = NULL;
	data->map.size_x = 0;
	data->map.size_y = 0;
	data->map.data = NULL;
	init_player(&data->map.player);
	init_colors(&data->map);
}

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->direction = 0;
}

void	init_colors(t_map *map)
{
	map->floor.r = -1;
	map->floor.g = -1;
	map->floor.b = -1;
	map->ceiling.r = -1;
	map->ceiling.g = -1;
	map->ceiling.b = -1;
}

int	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->data[i])
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
	return (0);
}