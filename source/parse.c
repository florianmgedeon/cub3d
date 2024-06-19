/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:55:26 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/19 11:07:02 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	parse_map(t_data *data, char *path)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nOpen");
		return (0);
	}
	ret = get_next_line(fd, &line);
	while (ret != 0)
	{
		if (ret == -1 || !manage_line(&data->map, line))
		{
			write(2, "Error\nParsing error\n", 21);
			return (0);
		}
		free(line);
		ret = get_next_line(fd, &line);
	}
	close(fd);
	return (1);
}

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
	if (line[i] == '\0')
		return (0);
	return (0);
}

bool	parse_texture(char **path, char *line)
{
	int		i;
	int		j;
	char	*new_path;

	i = 0;
	skip_spaces(line, &i);
	i += 2;
	skip_spaces(line, &i);
	j = i;
	while (line[j] && line[j] != ' ')
		j++;
	new_path = malloc((j - i + 1) * sizeof(char));
	if (!new_path)
		return (0);
	j = 0;
	while (line[i] && line[i] != ' ')
		new_path[j++] = line[i++];
	new_path[j] = '\0';
	*path = new_path;
	return (1);
}

int	parse_color(t_color *color, char *line)
{
	int		i;
	int		j;
	t_color	new_color;

	i = 0;
	skip_spaces(line, &i);
	i++;
	new_color.r = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	new_color.g = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	new_color.b = ft_atoi(line + i);
	*color = new_color;
	return (1);
}

bool	parse_map_data(t_map *map, char *line)
{
	int	i;
	int	j;
	int	*new_line;

	i = 0;
	new_line = malloc((ft_strlen(line)) * sizeof(int));
	if (!new_line)
		return (0);
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			new_line[j++] = -1;
		else if (line[i] == '1')
			new_line[j++] = 1;
		else if (line[i] == '0')
			new_line[j++] = 0;
		else if (is_player(line[i]))
		{
			new_line[j++] = 2;
			set_player(&map->player, j, i, line[i]);
		}
		return (0);
		i++;
	}
	map->data = new_line;
	return (1);
}
