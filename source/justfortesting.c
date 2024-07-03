
#include "../include/cub3d.h"

// just for testing
void	put_map(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (y < data->map.size_y)
	{
		while (x < data->map.size_x && data->map.data[y][x] != -2)
		{
			if (data->map.data[y][x] == 1)
				mlx_put_image_to_window(data->mlx, data->win, data->test_wall, x
					* 50, y * 50);
			x++;
			i++;
		}
		x = 0;
		y++;
	}
}

// just for testing
void	put_ray(t_data *data, int color, float end_x, float end_y)
{
	int	x;
	int	y;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	stepx;
	int	stepy;
	int	n;
	int	error;
	int	error2;

	x = data->map.player.x * data->map.tile_size;
	y = data->map.player.y * data->map.tile_size;
	x1 = end_x * data->map.tile_size;
	y1 = end_y * data->map.tile_size;
	dx = abs(x1 - x);
	dy = abs(y1 - y);
	stepx = (x1 > x) ? 1 : -1;
	stepy = (y1 > y) ? 1 : -1;
	n = (dx > dy) ? dx : dy;
	error = dx - dy;
	for (int i = 0; i < n; i++)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, color);
		error2 = 2 * error;
		if (error2 > -dy)
		{
			error -= dy;
			x += stepx;
		}
		if (error2 < dx)
		{
			error += dx;
			y += stepy;
		}
	}
}
