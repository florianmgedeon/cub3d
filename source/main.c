/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:36:10 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/25 14:17:31 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!arg_check(argc, argv))
		return (1);
	init_data(&data);
	if (!parse_map(&data, argv[1]))
		return (free_map(&data.map), 1);
	if (!map_check(&data.map))
		return (free_map(&data.map), 1);
	//mlx
	//run
	return (free_map(&data.map), 0);
}
