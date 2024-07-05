/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:23:55 by fgedeon           #+#    #+#             */
/*   Updated: 2024/07/04 16:32:17 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_ws(int keycode, t_data *data, float move_speed)
{
	if (keycode == 119)
	{
		if (data->map.data[(int)data->map.player.y][(int)(data->map.player.x
			+ data->map.player.dir_x * move_speed)] == 0)
			data->map.player.x += data->map.player.dir_x * move_speed;
		if (data->map.data[(int)(data->map.player.y + data->map.player.dir_y
				* move_speed)][(int)data->map.player.x] == 0)
			data->map.player.y += data->map.player.dir_y * move_speed;
	}
	if (keycode == 115)
	{
		if (data->map.data[(int)data->map.player.y][(int)(data->map.player.x
			- data->map.player.dir_x * move_speed)] == 0)
			data->map.player.x -= data->map.player.dir_x * move_speed;
		if (data->map.data[(int)(data->map.player.y - data->map.player.dir_y
				* move_speed)][(int)data->map.player.x] == 0)
			data->map.player.y -= data->map.player.dir_y * move_speed;
	}
}

void	move_ad(int keycode, t_data *data, float move_speed)
{
	if (keycode == 97)
	{
		if (data->map.data[(int)data->map.player.y][(int)(data->map.player.x
			+ data->map.player.dir_y * move_speed)] == 0)
			data->map.player.x += data->map.player.dir_y * move_speed;
		if (data->map.data[(int)(data->map.player.y - data->map.player.dir_x
				* move_speed)][(int)data->map.player.x] == 0)
			data->map.player.y -= data->map.player.dir_x * move_speed;
	}
	if (keycode == 100)
	{
		if (data->map.data[(int)data->map.player.y][(int)(data->map.player.x
			- data->map.player.dir_y * move_speed)] == 0)
			data->map.player.x -= data->map.player.dir_y * move_speed;
		if (data->map.data[(int)(data->map.player.y + data->map.player.dir_x
				* move_speed)][(int)data->map.player.x] == 0)
			data->map.player.y += data->map.player.dir_x * move_speed;
	}
}

void	rota(int keycode, t_data *d, float o_dir_x, float o_pl_x)
{
	float	angle;

	if (keycode == 65361)
		angle = -ROTATION_SPEED;
	else
		angle = ROTATION_SPEED;
	d->map.player.dir_x = d->map.player.dir_x * cos(angle) - d->map.player.dir_y
		* sin(angle);
	d->map.player.dir_y = o_dir_x * sin(angle) + d->map.player.dir_y
		* cos(angle);
	d->map.player.plane_x = d->map.player.plane_x * cos(angle)
		- d->map.player.plane_y * sin(angle);
	d->map.player.plane_y = o_pl_x * sin(angle) + d->map.player.plane_y
		* cos(angle);
}

// cleans up if window is closed with X/esc
int	x_the_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_data(data);
	exit(0);
}
