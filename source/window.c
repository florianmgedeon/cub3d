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

//changes window when keys are pressed
int	key_hook(int keycode, t_data *data)
{
    if (keycode == 100)//right
    {
        data->player.x += 10;
        data->player.ray_end_x = data->player.x + 15 + (60 * cos(data->player.angle));
        data->player.ray_end_y = data->player.y + 15 + (60 * sin(data->player.angle));
    }
    if (keycode == 115)//down
    {
        data->player.y += 10;
        data->player.ray_end_x = data->player.x + 15 + (60 * cos(data->player.angle));
        data->player.ray_end_y = data->player.y + 15 + (60 * sin(data->player.angle));
    }
    if (keycode == 97)//left
    {
        data->player.x -= 10;
        data->player.ray_end_x = data->player.x + 15 + (60 * cos(data->player.angle));
        data->player.ray_end_y = data->player.y + 15 + (60 * sin(data->player.angle));
    }
    if (keycode == 119)//up
    {
        data->player.y -= 10;
        data->player.ray_end_x = data->player.x + 15 + (60 * cos(data->player.angle));
        data->player.ray_end_y = data->player.y + 15 + (60 * sin(data->player.angle));
    }
    if (keycode == 65363)//right arrow
    {
        data->player.angle += 0.1;
        if (data->player.angle > 2 * PI)
            data->player.angle -= (2 * PI);
        data->player.ray_end_x = data->player.x + 15 + (60 * cos(data->player.angle));
        data->player.ray_end_y = data->player.y + 15 + (60 * sin(data->player.angle));
    }
    if (keycode == 65361)//left arrow
    {
        data->player.angle -= 0.1;
        if (data->player.angle < 0)
            data->player.angle += (2 * PI);
        data->player.ray_end_x = data->player.x + 15 + (60 * cos(data->player.angle));
        data->player.ray_end_y = data->player.y + 15 + (60 * sin(data->player.angle));
    }
    render(data);
    return (0);
}

//cleans up if window is closed
int	x_the_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	//destroy images with mlx_destroy_image
	mlx_destroy_image(data->mlx, data->test_player);
	//more destroy here

	mlx_destroy_display(data->mlx);
	//free map memory here
	free(data->mlx);
	exit(0);
}

//just for testing
void	put_map(t_data *data)
{
	int i = 0;
	while (i <= 1150) {
		mlx_put_image_to_window(data->mlx, data->win, data->test_wall, i, 0);
		i += 50; }
	i = 0;
	while (i <= 1150) {
		mlx_put_image_to_window(data->mlx, data->win, data->test_wall, i, 550);
		i += 50; }
	i = 0;
	while (i <= 550) {
		mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 0, i);
		i += 50; }
	i = 0;
	while (i <= 550) {
		mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 1150, i);
		i += 50; }
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 50);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 100);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 150);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 200);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 250);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 800, 400);
}

void put_ray(t_data *data)
{
	int x = data->player.x + 15;
	int y = data->player.y + 15;
	int x1 = data->player.ray_end_x;
	int y1 = data->player.ray_end_y;

	int dx = abs(x1 - x);
	int dy = abs(y1 - y);

	int stepx = (x1 > x) ? 1 : -1;
	int stepy = (y1 > y) ? 1 : -1;

	int n = (dx > dy) ? dx : dy;

	int error = dx - dy;
	int error2;

	for(int i = 0; i < n; i++)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, 0x00FFFFFF);
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

//puts images of the map to the window
void	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);//just for testing
	mlx_put_image_to_window(data->mlx, data->win, data->test_player, data->player.x, data->player.y);
	put_map(data);//just for testing
	put_ray(data);//just for testing
}

//creates the window & loads files to images
int start_win(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map.size_x, data->map.size_y, "cub3D");
	if (!data->win)
		return (0);
	data->test_player = mlx_xpm_file_to_image(data->mlx, "./textures/test_player.xpm",
			&data->test_height, &data->test_width);
	data->test_wall = mlx_xpm_file_to_image(data->mlx, "./textures/test_wall.xpm",
		&data->test_height, &data->test_width);
    
	return (1);
}
