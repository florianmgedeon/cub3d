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
    //just for testing INIT
    data.map.size_x = 8;
    data.map.size_y = 8;
    data.player.x = 2;
    data.player.y = 5;
    data.map.tile_size = 50;
    data.player.dir_x = -1;
    data.player.dir_y = 0;
    data.player.plane_x = 0;
    data.player.plane_y = 0.66;
    int test_content[] = {
    1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,};
    int rows = 8;
    int cols = 8;
    int **map = malloc(rows * sizeof(int *));
    if(map == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    for(int i = 0; i < rows; i++) {
        map[i] = &test_content[i*cols];
    }
    data.test_map = map;

    //belongs here:
    if (!start_win(&data))
        return (mlx_destroy_display(data.mlx), free(data.mlx), 1);
    render(&data);
    mlx_hook(data.win, 17, 0, x_the_win, &data);
    mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_loop(data.mlx);

    return (free(map), 0);
}