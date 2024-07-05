/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:36:10 by jkoupy            #+#    #+#             */
/*   Updated: 2024/07/04 21:56:32 by jkoupy           ###   ########.fr       */
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
	data.mlx = mlx_init();
	if (!data.mlx)
		return (free_data(&data), 1);
	if (!start_win(&data))
		return (free_data(&data), mlx_destroy_display(data.mlx),
			free(data.mlx), 1);
	calc_ray(&data);
	mlx_hook(data.win, 17, 0, x_the_win, &data);
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}

//main parsing function
//open the file and parse it line by line
bool	parse(t_data *data, char *path)
{
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nOpen"), 0);
	ret = get_next_line(fd, &line);
	while (ret != 0 && line)
	{
		if (ret == -1 || !manage_line(&data->map, line))
		{
			write(2, "Error\nParsing error\n", 21);
			free(line);
			while (get_next_line(fd, &line) != 0)
				free(line);
			return (0);
		}
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (close(fd) == -1)
		return (perror("Error\nClose"), 0);
	return (1);
}
