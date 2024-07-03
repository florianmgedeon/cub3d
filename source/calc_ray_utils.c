/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ray_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-03 13:31:26 by fgedeon           #+#    #+#             */
/*   Updated: 2024-07-03 13:31:26 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray_vars(t_data *data, t_ray *vars)
{
	vars->hit = 0;
	vars->map_x = (int)data->map.player.x;
	vars->map_y = (int)data->map.player.y;
	vars->camera_x = 2 * vars->i / (double)vars->w - 1;
	vars->ray_dir_x = data->map.player.dir_x + data->map.player.plane_x
		* vars->camera_x;
	vars->ray_dir_y = data->map.player.dir_y + data->map.player.plane_y
		* vars->camera_x;
	vars->delta_dist_x = fabs(1 / vars->ray_dir_x);
	vars->delta_dist_y = fabs(1 / vars->ray_dir_y);
}

void	calc_step_side(t_ray *vars, t_data *data)
{
	if (vars->ray_dir_x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (data->map.player.x - vars->map_x)
			* vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - data->map.player.x)
			* vars->delta_dist_x;
	}
	if (vars->ray_dir_y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (data->map.player.y - vars->map_y)
			* vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - data->map.player.y)
			* vars->delta_dist_y;
	}
}

void	calculate_hit(t_ray *vars, t_data *data)
{
	while (vars->hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			vars->side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			vars->side = 1;
		}
		if (data->map.data[vars->map_y][vars->map_x] > 0)
			vars->hit = 1;
	}
}

void	perpdist_and_put_ray(t_data *data, t_ray *vars)
{
	if (vars->side == 0)
		vars->perpwalldist = (vars->side_dist_x - vars->delta_dist_x);
	else
		vars->perpwalldist = (vars->side_dist_y - vars->delta_dist_y);
	put_ray(data, 16711680, data->map.player.x + vars->perpwalldist
		* vars->ray_dir_x, data->map.player.y + vars->perpwalldist
		* vars->ray_dir_y);
}

void	calculate_wall_properties(t_ray *vars)
{
	vars->h = SCREEN_HEIGHT;
	vars->lineheight = (int)(vars->h / vars->perpwalldist);
	vars->drawstart = -vars->lineheight / 2 + vars->h / 2;
	if (vars->drawstart < 0)
		vars->drawstart = 0;
	vars->drawend = vars->lineheight / 2 + vars->h / 2;
	if (vars->drawend >= vars->h)
		vars->drawend = vars->h - 1;
	vars->color_wall = 0;
	if (vars->tex == NORTH)
		vars->color_wall = 16711680;
	else if (vars->tex == SOUTH)
		vars->color_wall = 65280;
	else if (vars->tex == WEST)
		vars->color_wall = 255;
	else if (vars->tex == EAST)
		vars->color_wall = 16776960;
}
