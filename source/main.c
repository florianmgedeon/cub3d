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
    int        ray_length = 60;//just for testing

    //belongs into init_data function:
    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    //just for testing
    data.map.size_x = 1200;
    data.map.size_y = 600;
    data.player.x = 200;
    data.player.y = 200;
    data.player.angle = 90;
    data.player.ray_end_x = data.player.x + 15 + ray_length * cos(data.player.angle);
    data.player.ray_end_y = data.player.y + 15 + ray_length * sin(data.player.angle);
    int test_content[] = {
    1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,};
    data.test_content = test_content;

    //belongs here:
    if (!start_win(&data))
        return (mlx_destroy_display(data.mlx), free(data.mlx), 1);
    render(&data);
    mlx_hook(data.win, 17, 0, x_the_win, &data);
    mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_loop(data.mlx);

    return 0;
}