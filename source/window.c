/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:38:29 by fgedeon           #+#    #+#             */
/*   Updated: 2024/07/03 12:26:50 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//changes window when keys are pressed
int	key_hook(int keycode, t_data *data)
{
	float old_dir_x = data->map.player.dir_x;
	float old_plane_x = data->map.player.plane_x;
	float   move_speed = 0.1;

	if (keycode == 119)//W
	{
		if (data->map.data[(int)data->map.player.y][(int)(data->map.player.x + data->map.player.dir_x * move_speed)] == 0)
			data->map.player.x += data->map.player.dir_x * move_speed;
		if (data->map.data[(int)(data->map.player.y + data->map.player.dir_y * move_speed)][(int)data->map.player.x] == 0)
			data->map.player.y += data->map.player.dir_y * move_speed;
	}
	if (keycode == 97)//A
	{
		if (data->map.data[(int)data->map.player.y][(int)(data->map.player.x + data->map.player.dir_y * move_speed)] == 0)
			data->map.player.x += data->map.player.dir_y * move_speed;
		if (data->map.data[(int)(data->map.player.y - data->map.player.dir_x * move_speed)][(int)data->map.player.x] == 0)
			data->map.player.y -= data->map.player.dir_x * move_speed;
	}
	if (keycode == 115)//S
	{
		if (data->map.data[(int)data->map.player.y][(int)(data->map.player.x - data->map.player.dir_x * move_speed)] == 0)
			data->map.player.x -= data->map.player.dir_x * move_speed;
		if (data->map.data[(int)(data->map.player.y - data->map.player.dir_y * move_speed)][(int)data->map.player.x] == 0)
			data->map.player.y -= data->map.player.dir_y * move_speed;
	}
	if (keycode == 100)//D
	{
		if (data->map.data[(int)data->map.player.y][(int)(data->map.player.x - data->map.player.dir_y * move_speed)] == 0)
			data->map.player.x -= data->map.player.dir_y * move_speed;
		if (data->map.data[(int)(data->map.player.y + data->map.player.dir_x * move_speed)][(int)data->map.player.x] == 0)
			data->map.player.y += data->map.player.dir_x * move_speed;
	}
	if (keycode == 65361)//left arrow
	{
		data->map.player.dir_x = data->map.player.dir_x * cos(-0.1) - data->map.player.dir_y * sin(-0.1);
		data->map.player.dir_y = old_dir_x * sin(-0.1) + data->map.player.dir_y * cos(-0.1);
		data->map.player.plane_x = data->map.player.plane_x * cos(-0.1) - data->map.player.plane_y * sin(-0.1);
		data->map.player.plane_y = old_plane_x * sin(-0.1) + data->map.player.plane_y * cos(-0.1);
	}
	if (keycode == 65363)//right arrow
	{
		data->map.player.dir_x = data->map.player.dir_x * cos(0.1) - data->map.player.dir_y * sin(0.1);
		data->map.player.dir_y = old_dir_x * sin(0.1) + data->map.player.dir_y * cos(0.1);
		data->map.player.plane_x = data->map.player.plane_x * cos(0.1) - data->map.player.plane_y * sin(0.1);
		data->map.player.plane_y = old_plane_x * sin(0.1) + data->map.player.plane_y * cos(0.1);
	}
	if (keycode == 65307)//esc
		x_the_win(data);
	render(data);
	return (0);
}


//cleans up if window is closed with the top right X
int	x_the_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->test_player);
	mlx_destroy_image(data->mlx, data->test_wall);
	mlx_destroy_window(data->mlx, data->win2);
	//more destroy here

	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_data(data);


	exit(0);
}

//just for testing
void	put_map(t_data *data)
{
	int i = 0;
	int x = 0;
	int y = 0;

	while (y < data->map.size_y)
	{
		while (x < data->map.size_x && data->map.data[y][x] != -2)
		{
			if (data->map.data[y][x] == 1)
				mlx_put_image_to_window(data->mlx, data->win, data->test_wall, x * 50, y * 50);
			x++;
			i++;
		}
		x = 0;
		y++;
	}
}

//draws the ray according to the DDA algorithm endpoints
void put_ray(t_data *data, int color, float end_x, float end_y)
{
	int x = data->map.player.x * data->map.tile_size;
	int y = data->map.player.y * data->map.tile_size;
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

int colorToInt(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

//draws the wall according to calc_ray function's i, drawStart and drawEnd, color
void put_wall(t_data *data, int i, int drawStart, int drawEnd, int color, int x_of_tex, int tex)
{
	int col_width = SCREEN_WIDTH / NBR_RAYS;
	int colx = i * col_width;
	int y = 0;

	while (colx < (i + 1) * col_width)
	{
		y = 0;
		while (y < drawStart)
		{
			mlx_pixel_put(data->mlx, data->win2, colx, y, colorToInt(data->map.ceiling));
			y++;
		}
		y = 0;
		while (drawStart + y < drawEnd)
		{	
			mlx_pixel_put(data->mlx, data->win2, colx, drawStart + y, color);
			y++;
		}
		y = 0;
		while (y + drawEnd < SCREEN_HEIGHT)
		{
			mlx_pixel_put(data->mlx, data->win2, colx, y + drawEnd, colorToInt(data->map.floor));
			y++;
		}
		colx++;
	}
}

int what_texture(int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray_dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

//calculates the ray endpoints and the distance to the wall
void calc_ray(t_data *data)
{
	int i = 0;
	int w = NBR_RAYS;
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	int step_x;
	int step_y;
	int hit = 0;
	int side;

	while (i <= w)
	{
		hit = 0;
		map_x = (int)data->map.player.x;
		map_y = (int)data->map.player.y;
		camera_x = 2 * i / (double)w - 1;
		ray_dir_x = data->map.player.dir_x + data->map.player.plane_x * camera_x;
		ray_dir_y = data->map.player.dir_y + data->map.player.plane_y * camera_x;
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)//init step and side_dist
		{
			step_x = -1;
			side_dist_x = (data->map.player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->map.player.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->map.player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->map.player.y) * delta_dist_y;
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
			if (data->map.data[map_y][map_x] > 0)
				hit = 1;
		}
		float perpWallDist;
		if(side == 0)
			perpWallDist = (side_dist_x - delta_dist_x);
		else          
			perpWallDist = (side_dist_y - delta_dist_y);
		put_ray(data, 16711680, data->map.player.x + perpWallDist * ray_dir_x, data->map.player.y + perpWallDist * ray_dir_y);
		
		int tex = what_texture(side, ray_dir_x, ray_dir_y);
		//calc height, draw start and draw end, color wall
		int h = SCREEN_HEIGHT;

		int lineHeight = (int)(h / perpWallDist);
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)
			drawEnd = h - 1;
		
		int color_wall = 0;
		if (tex == NORTH)
			color_wall = 16711680;
		else if (tex == SOUTH)
			color_wall = 65280;
		else if (tex == WEST)
			color_wall = 255;
		else if (tex == EAST)
			color_wall = 16776960;
		//printf("i: %d, drawStart: %d, drawEnd: %d\n", i, drawStart, drawEnd);
		int x_of_tex = (data->map.player.x + perpWallDist * ray_dir_x) - (int)(data->map.player.x + perpWallDist * ray_dir_x);
		put_wall(data, i, drawStart, drawEnd, color_wall, x_of_tex, tex);
		
		i++;
	}
}

//puts images of the map to the window
void	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);//just for testing
	put_map(data);//just for testing
	calc_ray(data);
}

//creates the window & loads files to images
int start_win(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map.size_x * data->map.tile_size, data->map.size_y * data->map.tile_size, "cub3D");
	if (!data->win)
		return (0);
	data->test_player = mlx_xpm_file_to_image(data->mlx, "./textures/test_player.xpm",
			&data->test_height, &data->test_width);
	data->test_wall = mlx_xpm_file_to_image(data->mlx, "./textures/test_wall.xpm",
		&data->test_height, &data->test_width);
	
	return (1);
}

int *save_texture(t_data *data, char *path)
{
	int tex;
	int *texture;
	void *tex_ptr;

	tex = TEXTURE_SIZE;
	tex_ptr = mlx_xpm_file_to_image(data->mlx, path, &tex, &tex);
	texture = (int *)mlx_get_data_addr(tex_ptr, &tex, &tex, &tex);
	return (texture);
}

//new window for 3D
int start_win2(t_data *data)
{
	data->win2 = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!data->win2)
		return (0);
	data->texture = malloc(sizeof(int *) * 4);
	if (!data->texture)
		return (0);
	//save texture file to image then image to address function
	data->texture[NORTH] = save_texture(data, data->map.no_path);
	data->texture[SOUTH] = save_texture(data, data->map.so_path);
	data->texture[WEST] = save_texture(data, data->map.we_path);
	data->texture[EAST] = save_texture(data, data->map.ea_path);
	if (!data->texture[NORTH] || !data->texture[SOUTH] || !data->texture[WEST] || !data->texture[EAST])
		return (0);
	return (1);
}
