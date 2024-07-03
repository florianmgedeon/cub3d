/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:46:55 by jkoupy            #+#    #+#             */
/*   Updated: 2024/07/03 19:52:17 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//set the player position and angle
//error if multiple players
bool	set_player(t_map *map, int x, char c)
{
	t_player	*player;

	player = &map->player;
	if (player->x != -1 || player->y != -1 || player->dir_x != -2
		|| player->dir_y != -2 || player->plane_x != -2
		|| player->plane_y != -2)
		return (write(2, "Error\nMultiple players in the map\n", 35), false);
	player->x = x + 0.5;
	player->y = map->size_y + 0.5;
	set_dir(player, c);
	set_plane(player, c);
	return (true);
}

//set the player direction
void	set_dir(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (c == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (c == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (c == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

void	set_plane(t_player *player, char c)
{
	if (c == 'N')
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (c == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (c == 'S')
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (c == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

//check argc and file extension
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

//realloc the map when a new line is added
int	**map_add_line(t_map *map, int *new_line)
{
	int	**new_map_data;
	int	i;

	new_map_data = malloc((map->size_y) * sizeof(int *));
	if (!new_map_data)
		return (0);
	i = 0;
	while (i < map->size_y - 1)
	{
		new_map_data[i] = map->data[i];
		i++;
	}
	new_map_data[i] = new_line;
	free(map->data);
	return (new_map_data);
}
