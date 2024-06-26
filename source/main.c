/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:36:10 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/26 15:55:32 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!arg_check(argc, argv))
		return (1);
	init_data(&data);
	if (!parse(&data, argv[1]))
		return (free_data(&data), 1);
	if (!map_check(data.map))
		return (free_data(&data), 1);
	print_map(data.map);
	//mlx
	//run
	return (free_data(&data), 0);
}

//main parsing function
//open the file and parse it line by line
bool	parse(t_data *data, char *path)
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
			close(fd);
			return (0);
		}
		free(line);
		ret = get_next_line(fd, &line);
	}
	close(fd);
	return (1);
}