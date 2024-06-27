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
        data->player.x += 10;
    if (keycode == 115)//down
        data->player.y += 10;
    if (keycode == 97)//left
        data->player.x -= 10;
    if (keycode == 119)//up
        data->player.y -= 10;
    if (keycode == 65363)//right arrow
    {
        data->player.angle_rad -= 0.1;
        if (data->player.angle_rad > 2 * PI)
            data->player.angle_rad -= (2 * PI);
    }
    if (keycode == 65361)//left arrow
    {
        data->player.angle_rad += 0.1;
        if (data->player.angle_rad < 0)
            data->player.angle_rad += (2 * PI);
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
	int x1 = end_x;
	int y1 = end_y;

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
    float testangle = 0;
    int mapx = 0;
    int mapy = 0;

	//VERTICAL
    while (i < 1)
    {
        testangle = data->player.angle_rad + (i * 0.017);
        if (testangle < 0)
            testangle += (2 * PI);
        //mytan = tan(PI - testangle - 0.0001);
        mytan = tan(testangle);
        dof = 0;
        if(cos(testangle) <= -0.0001)//left
        {
            end_x = (((int)(data->player.x / 50) * 50) - 0.0001);
            end_y = (data->player.x - end_x) * mytan + data->player.y;
            xoffset = -50;
            yoffset = -xoffset * mytan;
        }
        else if(cos(testangle) >= 0.0001)//right
        {
            end_x = (((int)(data->player.x / 50) * 50) + 50);
            end_y = (data->player.x - end_x) * mytan + data->player.y;
            xoffset = 50;
            yoffset = -xoffset * mytan;
        }
        else //up or down
        {
            end_x = data->player.x;
            end_y = data->player.y;
            dof = 8;
        }
        while (dof < 8)
        {
            //map_index = (int)end_x / 50 + (((int)end_y / 50) * 8);
            mapx = (int)end_x / 50;
            mapy = (int)end_y / 50;
            map_index = mapy * 8 + mapx;
            if (map_index > 0 && map_index < 64 && data->test_content[map_index] == 1)
                dof = 8;
            else
            {
                end_x += xoffset;
                end_y += yoffset;
                dof++;
            }
        }
        //Draw both for now, later only one
        put_ray(data, 16711680, end_x, end_y);
        
        //HORIZONTAL
        dof = 0;
        mytan = 1/mytan;
        if(sin(testangle) >= 0.0001)//up
        {
            end_y = (((int)(data->player.y / 50) * 50) - 0.0001);
            end_x = (data->player.y - end_y) * mytan + data->player.x;
            yoffset = -50;
            xoffset = -yoffset * mytan;
        }
        else if(sin(testangle) <= -0.0001)//down
        {
            end_y = (((int)(data->player.y / 50) * 50) + 50);
            end_x = (data->player.y - end_y) * mytan + data->player.x;
            yoffset = 50;
            xoffset = -yoffset * mytan;
        }
        else //left or right
        {
            end_x = data->player.x;
            end_y = data->player.y;
            dof = 8;
        }
        while (dof < 8)
        {
            //map_index = (int)end_x / 50 + (((int)end_y / 50) * 8);
            mapx = (int)end_x / 50;
            mapy = (int)end_y / 50;
            map_index = mapy * 8 + mapx;
            if (map_index > 0 && map_index < 64 && data->test_content[map_index] == 1)
                dof = 8;
            else
            {
                end_x += xoffset;
                end_y += yoffset;
                dof++;
            }
        }
        //Draw both for now, later only one
        put_ray(data, 32768, end_x, end_y);
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
