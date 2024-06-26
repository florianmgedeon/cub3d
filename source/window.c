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
	int x = 0;
	int y = 0;

	while (y < 8)
	{
		while (x < 8)
		{
			if (data->test_content[i] == 1)
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
	int x = data->player.x + 15;
	int y = data->player.y + 15;
	int x1 = 0;
	int y1 = 0;
	if (end_x == 0 || end_y == 0)
	{
		x1 = data->player.ray_end_x;
		y1 = data->player.ray_end_y;
	}
	else
	{
		x1 = end_x;
		y1 = end_y;
	}

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

void put_more_rays(t_data *data)
{
    int i = 0;
    float end_x = 0;
    float end_y = 0;
    float mytan = 0;
    float xoffset = 0;
    float yoffset = 0;
    int dof = 0;
    int map_index = 0;

	//VERTICAL
    while (i < 1)
    {
        mytan = tan(PI - data->player.angle - 0.0000001);
        if(cos(data->player.angle) >= 0.0001) //looking left
        {
            end_x = (((int)(data->player.x / 50) * 50) + 50);
            end_y = (data->player.x - end_x) * mytan + data->player.y;
            xoffset = 50;
            yoffset = -xoffset * mytan;
        }
        else if(cos(data->player.angle) <= -0.0001) //looking right
        {
            end_x = (((int)(data->player.x / 50) * 50) - 0.0000001);
            end_y = (data->player.x - end_x) * mytan + data->player.y;
            xoffset = -50;
            yoffset = -xoffset * mytan;
        }
        else //looking up or down
        {
            end_x = data->player.x;
            end_y = data->player.y;
            dof = 8;
        }
        while (dof < 8)
        {
            map_index = (int)end_x / 50 + (int)end_y / 50 * 8;
            if (map_index < 64 && data->test_content[map_index] == 1)
                dof = 8;
            else
            {
                end_x += xoffset;
                end_y += yoffset;
                dof++;
            }
        }
        put_ray(data, 16711680, end_x, end_y);
        i++;
    }
}

//puts images of the map to the window
void	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);//just for testing
	mlx_put_image_to_window(data->mlx, data->win, data->test_player, data->player.x, data->player.y);
	put_map(data);//just for testing
	put_more_rays(data);//just for testing
	//put_ray(data, 16777215, 0, 0);//just for testing MAIN RAY
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
