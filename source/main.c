/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:36:10 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/18 15:00:59 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main()
{
    t_data	data;

    //belongs into init_data function:
    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    data.map.size_x = 600;
    data.map.size_y = 400;

    //belongs here:
    if (!start_win(&data))
        return (mlx_destroy_display(data.mlx), free(data.mlx), 1);
    //here do the: render(&data);
    mlx_hook(data.win, 17, 0, x_the_win, &data);
	mlx_loop(data.mlx);
    
    return 0;
}