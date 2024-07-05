/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:31:26 by fgedeon           #+#    #+#             */
/*   Updated: 2024/07/05 10:15:08 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray_vars(t_data *data, t_ray *vars)
{
	vars->map_x = (int)data->map.player.x;
	vars->map_y = (int)data->map.player.y;
	vars->camera_x = 2 * vars->ray_i / (double)vars->s_width - 1;
	vars->ray_dir_x = data->map.player.dir_x + data->map.player.plane_x
		* vars->camera_x;
	vars->ray_dir_y = data->map.player.dir_y + data->map.player.plane_y
		* vars->camera_x;
	vars->step_dist_x = fabs(1 / vars->ray_dir_x);
	vars->step_dist_y = fabs(1 / vars->ray_dir_y);
}

void	calc_step_side(t_ray *vars, t_data *data)
{
	if (vars->ray_dir_x < 0)
	{
		vars->first_dist_x = (data->map.player.x - vars->map_x)
			* vars->step_dist_x;
		vars->step_x = -1;
	}
	else
	{
		vars->first_dist_x = (vars->map_x + 1.0 - data->map.player.x)
			* vars->step_dist_x;
		vars->step_x = 1;
	}
	if (vars->ray_dir_y < 0)
	{
		vars->first_dist_y = (data->map.player.y - vars->map_y)
			* vars->step_dist_y;
		vars->step_y = -1;
	}
	else
	{
		vars->first_dist_y = (vars->map_y + 1.0 - data->map.player.y)
			* vars->step_dist_y;
		vars->step_y = 1;
	}
}

void	calc_wall_dist(t_ray *vars, t_data *data)
{
	while (data->map.data[vars->map_y][vars->map_x] != 1)
	{
		if (vars->first_dist_x < vars->first_dist_y)
		{
			vars->wall_side = VERTICAL;
			vars->first_dist_x += vars->step_dist_x;
			vars->map_x += vars->step_x;
		}
		else
		{
			vars->wall_side = HORIZONTAL;
			vars->first_dist_y += vars->step_dist_y;
			vars->map_y += vars->step_y;
		}
	}
	if (vars->wall_side == VERTICAL)
		vars->wall_dist = (vars->first_dist_x - vars->step_dist_x);
	else
		vars->wall_dist = (vars->first_dist_y - vars->step_dist_y);
}

void	calculate_wall_properties(t_data *d, t_ray *vars)
{
	vars->s_height = SCREEN_HEIGHT;
	if (vars->wall_dist < 0.01)
		vars->wall_dist = 0.01;
	vars->wall_height = (int)(vars->s_height / vars->wall_dist);
	vars->wall_top = (vars->s_height / 2) - (vars->wall_height / 2);
	vars->wall_bottom = (vars->s_height / 2) + (vars->wall_height / 2);
	if (vars->wall_side == VERTICAL)
		vars->wall_x = (d->map.player.y + vars->wall_dist
				* vars->ray_dir_y);
	else
		vars->wall_x = (d->map.player.x + vars->wall_dist
				* vars->ray_dir_x);
}
