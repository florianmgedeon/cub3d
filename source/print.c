/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:12:02 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/27 13:49:41 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map(t_map map)
{
	int	i;
	int	j;

	i = 0;
	printf("NO: %s\nSO: %s\n", map.no_path, map.so_path);
	printf("WE: %s\nEA: %s\n", map.we_path, map.ea_path);
	printf("F: %d %d %d\n", map.floor.r, map.floor.g, map.floor.b);
	printf("C: %d %d %d\n", map.ceiling.r, map.ceiling.g, map.ceiling.b);
	printf("size_x: %d\nsize_y: %d\n\n", map.size_x, map.size_y);
	printf("player: %f %f %f\n", map.player.x, map.player.y, map.player.direction);
	printf("map:\n");
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x && map.data[i][j] != -2)
		{
			if (map.data[i][j] == -1)
				printf(" ");
			else
				printf("%i", map.data[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

//print line of ints
void	print_line(int *line, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%i", line[i]);
		i++;
	}
	printf("\n");
}
