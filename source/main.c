/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:36:10 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/19 11:00:21 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		write(2, "Error\nWrong number of arguments\n", 32);
		return (0);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		write(2, "Error\nWrong file extension\n", 28);
		return (0);
	}
	if (!parse_map(&data, argv[1]))
		return (0);
	//mlx
	//run
	return (0);
}
