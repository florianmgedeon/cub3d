/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:38:29 by fgedeon           #+#    #+#             */
/*   Updated: 2024/07/03 17:21:34 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// changes window when keys are pressed (WASD, left/right arrows, esc)
int	key_hook(int keycode, t_data *data)
{
	float	old_dir_x;
	float	old_plane_x;
	float	move_speed;

	old_dir_x = data->map.player.dir_x;
	old_plane_x = data->map.player.plane_x;
	move_speed = 0.1;
	if (keycode == 119 || keycode == 115)
		move_ws(keycode, data, move_speed);
	else if (keycode == 97 || keycode == 100)
		move_ad(keycode, data, move_speed);
	else if (keycode == 65361 || keycode == 65363)
		rota(keycode, data, old_dir_x, old_plane_x);
	if (keycode == 65307)
		x_the_win(data);
	mlx_clear_window(data->mlx, data->win); // just for testing
	put_map(data);                          // just for testing
	calc_ray(data);
	return (0);
}

// draws the wall
void	put_wall(t_data *data, t_ray *vars)
{
	int	colx;
	int	y;

	colx = vars->i * (SCREEN_WIDTH / NBR_RAYS);
	y = 0;
	while (colx < (vars->i + 1) * (SCREEN_WIDTH / NBR_RAYS))
	{
		y = 0;
		while (y < vars->drawstart)
		{
			mlx_pixel_put(data->mlx, data->win2, colx, y,
				colortoint(data->map.ceiling));
			y++;
		}
		draw_texture(data, vars, colx);
		y = 0;
		while (y + vars->drawend < SCREEN_HEIGHT)
		{
			mlx_pixel_put(data->mlx, data->win2, colx, y + vars->drawend,
				colortoint(data->map.floor));
			y++;
		}
		colx++;
	}
}

int	what_texture(int side, double ray_dir_x, double ray_dir_y)
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

// calculates the ray endpoints and the distance to the wall
void	calc_ray(t_data *data)
{
	t_ray	vars;
	float	x_of_tex;

	vars.i = 0;
	vars.w = NBR_RAYS;
	while (vars.i <= vars.w)
	{
		init_ray_vars(data, &vars);
		calc_step_side(&vars, data);
		calculate_hit(&vars, data);
		perpdist_and_put_ray(data, &vars);
		vars.tex = what_texture(vars.side, vars.ray_dir_x, vars.ray_dir_y);
		calculate_wall_properties(data, &vars);
		x_of_tex = 0;
		if (vars.side == 0)
			x_of_tex = (data->map.player.y + vars.perpwalldist
					* vars.ray_dir_y);
		else
			x_of_tex = (data->map.player.x + vars.perpwalldist
					* vars.ray_dir_x);
		put_wall(data, &vars);
		vars.i++;
	}
}
