/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:55:26 by jkoupy            #+#    #+#             */
/*   Updated: 2024/07/04 21:20:37 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//manage lines depending on the first character
bool	manage_line(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && map->data == NULL)
		return (parse_texture(&map->no_path, line));
	if (line[i] == 'S' && line[i + 1] == 'O' && map->data == NULL)
		return (parse_texture(&map->so_path, line));
	if (line[i] == 'W' && line[i + 1] == 'E' && map->data == NULL)
		return (parse_texture(&map->we_path, line));
	if (line[i] == 'E' && line[i + 1] == 'A' && map->data == NULL)
		return (parse_texture(&map->ea_path, line));
	if (line[i] == 'F' && map->data == NULL)
		return (parse_color(&map->floor, line));
	if (line[i] == 'C' && map->data == NULL)
		return (parse_color(&map->ceiling, line));
	if (line[i] == '1')
		return (parse_map_data(map, line));
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}

//parse the texture path
bool	parse_texture(char **path, char *line)
{
	int		i;
	int		j;
	char	*new_path;

	if (!line || !*line || *path)
		return (0);
	i = 0;
	skip_spaces(line, &i);
	i += 2;
	skip_spaces(line, &i);
	new_path = malloc(ft_strlen(line + i) * sizeof(char));
	if (!new_path)
		return (false);
	j = 0;
	while (line[i] && line[i] != '\n' && line[i] != ' ' && line[i] != '\0')
		new_path[j++] = line[i++];
	new_path[j] = '\0';
	*path = new_path;
	return (true);
}

//parse the color format 
//[space][C/F][space][int][space][,][space][int][space][,][space][int]
//spaces are optional, ints have to start with a digit
bool	parse_color(t_color *color, char *line)
{
	int		i;

	i = 0;
	skip_spaces(line, &i);
	i++;
	skip_spaces(line, &i);
	if (i < (int)ft_strlen(line) && ft_isdigit(line[i]))
		color->r = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	i++;
	skip_spaces(line, &i);
	if (i < (int)ft_strlen(line) && ft_isdigit(line[i]))
		color->g = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	i++;
	skip_spaces(line, &i);
	if (i < (int)ft_strlen(line) && ft_isdigit(line[i]))
		color->b = ft_atoi(line + i);
	return (true);
}

//parse the map data and add it to the map
bool	parse_map_data(t_map *map, char *line)
{
	int	i;
	int	*new_line;

	i = 0;
	new_line = malloc((ft_strlen(line) + 1) * sizeof(int));
	if (!new_line)
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			new_line[i++] = -1;
		else if (line[i] == '1')
			new_line[i++] = 1;
		else if (line[i] == '0' || (is_player(line[i])
				&& set_player(map, i, line[i])))
			new_line[i++] = 0;
		else
			return (free(new_line), 0);
	}
	new_line[i] = -2;
	update_map_size(map, i);
	map->data = map_add_line(map, new_line);
	if (!map->data)
		return (free(new_line), 0);
	return (1);
}

//updates size_x and size_y of the map
void	update_map_size(t_map *map, int x)
{
	if (x > map->size_x)
		map->size_x = x;
	map->size_y++;
}
