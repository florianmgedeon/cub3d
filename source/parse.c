/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:55:26 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/26 16:33:23 by jkoupy           ###   ########.fr       */
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
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (parse_texture(&map->no_path, line));
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (parse_texture(&map->so_path, line));
	if (line[i] == 'W' && line[i + 1] == 'E')
		return (parse_texture(&map->we_path, line));
	if (line[i] == 'E' && line[i + 1] == 'A')
		return (parse_texture(&map->ea_path, line));
	if (line[i] == 'F')
		return (parse_color(&map->floor, line));
	if (line[i] == 'C')
		return (parse_color(&map->ceiling, line));
	if (line[i] == '1')
		return (parse_map_data(map, line));
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}

//parse the texture path,
bool	parse_texture(char **path, char *line)
{
	int		i;
	int		j;
	char	*new_path;

	if (!line || !*line)
		return (0);
	i = 0;
	skip_spaces(line, &i);
	i += 2;
	skip_spaces(line, &i);
	new_path = malloc(ft_strlen(line + i) * sizeof(char));
	if (!new_path)
		return (0);
	j = 0;
	while (line[i] && line[i] != '\n' && line[i] != ' ' && line[i] != '\0')
		new_path[j++] = line[i++];
	new_path[j] = '\0';
	*path = new_path;
	return (1);
}

bool	parse_color(t_color *color, char *line)
{
	int		i;
	t_color	new_color;

	i = 0;
	skip_spaces(line, &i);
	i++;
	new_color.r = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	skip_spaces(line, &i);
	new_color.g = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	skip_spaces(line, &i);
	new_color.b = ft_atoi(line + i);
	*color = new_color;
	return (true);
}

bool	parse_map_data(t_map *map, char *line)
{
	int	i;
	int	*new_line;

	i = 0;
	new_line = malloc((ft_strlen(line)) * sizeof(int));
	if (!new_line)
		return (0);
	while (line[i])
	{
		if (line[i] == ' ')
			new_line[i++] = -1;
		else if (line[i] == '1')
			new_line[i++] = 1;
		else if (line[i] == '0')
			new_line[i++] = 0;
		else if (is_player(line[i]) && set_player(map, i, line[i]))
			new_line[i++] = 2;
		else if (line[i] == '\0' || line[i] == '\n')
			break ;
		else
			return (0);
	}
	update_map_size(map, i);
	map->data = map_add_line(map, new_line);
	return (1);
}

void	update_map_size(t_map *map, int x)
{
	if (x > map->size_x)
		map->size_x = x;
	map->size_y++;
}

