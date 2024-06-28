/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-26 11:38:29 by fgedeon           #+#    #+#             */
/*   Updated: 2024-06-26 11:38:29 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//changes window when keys are pressed - CHANGE TO DIR VECTOR MULTIPLICATION

int	key_hook(int keycode, t_data *data)
{
    float old_dir_x = data->player.dir_x;
    float old_plane_x = data->player.plane_x;
    // if (keycode == 119)//W
    // {
    //     data->player.x += cos(data->player.angle_rad) / 10;
    //     data->player.y -= sin(data->player.angle_rad) / 10;
    // }
    // if (keycode == 97)//A
    // {
    //     data->player.x -= sin(data->player.angle_rad) / 10;
    //     data->player.y -= cos(data->player.angle_rad) / 10;
    // }
    // if (keycode == 115)//S
    // {
    //     data->player.x -= cos(data->player.angle_rad) / 10;
    //     data->player.y += sin(data->player.angle_rad) / 10;
    // }
    // if (keycode == 100)//D
    // {
    //     data->player.x += sin(data->player.angle_rad) / 10;
    //     data->player.y += cos(data->player.angle_rad) / 10;
    // }
    if (keycode == 65361)//left arrow
    {
        data->player.dir_x = data->player.dir_x * cos(-0.1) - data->player.dir_y * sin(-0.1);
        data->player.dir_y = old_dir_x * sin(-0.1) + data->player.dir_y * cos(-0.1);
        data->player.plane_x = data->player.plane_x * cos(-0.1) - data->player.plane_y * sin(-0.1);
        data->player.plane_y = old_plane_x * sin(-0.1) + data->player.plane_y * cos(-0.1);
    }
    if (keycode == 65363)//right arrow
    {
        data->player.dir_x = data->player.dir_x * cos(0.1) - data->player.dir_y * sin(0.1);
        data->player.dir_y = old_dir_x * sin(0.1) + data->player.dir_y * cos(0.1);
        data->player.plane_x = data->player.plane_x * cos(0.1) - data->player.plane_y * sin(0.1);
        data->player.plane_y = old_plane_x * sin(0.1) + data->player.plane_y * cos(0.1);
    }
    render(data);
    return (0);
}


//cleans up if window is closed
int	x_the_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->test_player);
    mlx_destroy_image(data->mlx, data->test_wall);
	//more destroy here

	mlx_destroy_display(data->mlx);
	free(data->test_map);
	free(data->mlx);
	exit(0);
}

//just for testing
void	put_map(t_data *data)
{
	int i = 0;
	int x = 0;
	int y = 0;

	while (y < 8)
	{
		while (x < 8)
		{
			if (data->test_map[y][x] == 1)
				mlx_put_image_to_window(data->mlx, data->win, data->test_wall, x * 50, y * 50);
			x++;
			i++;
		}
		x = 0;
		y++;
	}
}

void put_ray(t_data *data, int color, float end_x, float end_y)
{
	int x = data->player.x * data->map.tile_size;
	int y = data->player.y * data->map.tile_size;
	int x1 = end_x * data->map.tile_size;
	int y1 = end_y * data->map.tile_size;

	int dx = abs(x1 - x);
	int dy = abs(y1 - y);

	int stepx = (x1 > x) ? 1 : -1;
	int stepy = (y1 > y) ? 1 : -1;

	int n = (dx > dy) ? dx : dy;

	int error = dx - dy;
	int error2;

	for(int i = 0; i < n; i++)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, color);
		error2 = 2 * error;

		if(error2 > -dy)
		{
			error -= dy;
			x += stepx;
		}

		if(error2 < dx)
		{
			error += dx;
			y += stepy;
		}
	}

}

void calc_ray(t_data *data)
{
    int i = 0;
    int w = 1;
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x = (int)data->player.x;
    int map_y = (int)data->player.y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    int hit = 0;
    int side;

    while (i < w)
    {
        camera_x = 2 * i / w - 1;
        ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
        ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
        delta_dist_x = fabs(1 / ray_dir_x);
        delta_dist_y = fabs(1 / ray_dir_y);
        if (ray_dir_x < 0)//init step and side_dist
        {
            step_x = -1;
            side_dist_x = (data->player.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - data->player.x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (data->player.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - data->player.y) * delta_dist_y;
        }
        while (hit == 0)//DDA loop
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;

            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (data->test_map[map_y][map_x] > 0)
                hit = 1;
        }
        float perpWallDist;
        if(side == 0) 
            perpWallDist = (side_dist_x - delta_dist_x);
        else          
            perpWallDist = (side_dist_y - delta_dist_y);
        if (side == 0)
        {
            //put_ray(data, 30000000, data->player.x + side_dist_x, data->player.y);
            put_ray(data, 16711680, data->player.x + perpWallDist * ray_dir_x, data->player.y + perpWallDist * ray_dir_y);
        }
        else
        {
            //put_ray(data, 70000000, data->player.x + side_dist_y, data->player.y);
            put_ray(data, 16711680, data->player.x + perpWallDist * ray_dir_x, data->player.y + perpWallDist * ray_dir_y);
        }
        i++;
    }
}

//puts images of the map to the window
void	render(t_data *data)
{
	//mlx_clear_window(data->mlx, data->win);//just for testing
	//mlx_put_image_to_window(data->mlx, data->win, data->test_player, data->player.x * data->map.tile_size, data->player.y * data->map.tile_size);
	put_map(data);//just for testing
	calc_ray(data);
}

//creates the window & loads files to images
int start_win(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map.size_x * data->map.tile_size *2, data->map.size_y * data->map.tile_size *2, "cub3D");
	if (!data->win)
		return (0);
	data->test_player = mlx_xpm_file_to_image(data->mlx, "./textures/test_player.xpm",
			&data->test_height, &data->test_width);
	data->test_wall = mlx_xpm_file_to_image(data->mlx, "./textures/test_wall.xpm",
		&data->test_height, &data->test_width);
    
	return (1);
}
