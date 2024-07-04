/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:30:08 by jkoupy            #+#    #+#             */
/*   Updated: 2024/07/04 15:56:11 by jkoupy           ###   ########.fr       */
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
	data->texture = NULL;
	init_player(&data->map.player);
	init_colors(&data->map);
}

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->dir_x = -2;
	player->dir_y = -2;
	player->plane_x = -2;
	player->plane_y = -2;
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

//free the allocated data
int	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.size_y && data->map.data && data->map.data[i])
		free(data->map.data[i++]);
	free(data->map.data);
	free(data->map.no_path);
	free(data->map.so_path);
	free(data->map.we_path);
	free(data->map.ea_path);
	if (data->texture)
	{
		i = 0;
		while (i < 4)
		{
			if (data->texture[i])
				free(data->texture[i++]);
		}
		free(data->texture);
	}
	return (0);
}
