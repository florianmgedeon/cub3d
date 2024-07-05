/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:40:51 by fgedeon           #+#    #+#             */
/*   Updated: 2024/07/05 10:11:11 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// draws the wall
void	put_wall(t_data *data, t_ray *vars)
{
	int	colx;
	int	y;

	colx = vars->ray_i * (SCREEN_WIDTH / NBR_RAYS);
	y = 0;
	while (colx < (vars->ray_i + 1) * (SCREEN_WIDTH / NBR_RAYS))
	{
		y = 0;
		while (y < vars->wall_top)
		{
			mlx_pixel_put(data->mlx, data->win, colx, y,
				colortoint(data->map.ceiling));
			y++;
		}
		draw_texture(data, vars, colx);
		y = 0;
		while (y + vars->wall_bottom < SCREEN_HEIGHT)
		{
			mlx_pixel_put(data->mlx, data->win, colx, y + vars->wall_bottom,
				colortoint(data->map.floor));
			y++;
		}
		colx++;
	}
}

// calculates the x and y of the texture to draw in the wall
void	draw_texture(t_data *data, t_ray *vars, int colx)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	y = 0;
	while (vars->wall_top + y < vars->wall_bottom)
	{
		if (vars->wall_top + y < 0)
		{
			y++;
			continue ;
		}
		if (vars->wall_top + y >= SCREEN_HEIGHT)
			break ;
		tex_x = (int)((vars->wall_x - (int)vars->wall_x) * TEXTURE_SIZE);
		if (vars->tex == SOUTH || vars->tex == WEST)
			tex_x = TEXTURE_SIZE - tex_x - 1;
		tex_y = (y * TEXTURE_SIZE) / (vars->wall_bottom - vars->wall_top);
		color = data->texture[vars->tex][tex_x + tex_y * TEXTURE_SIZE];
		mlx_pixel_put(data->mlx, data->win, colx, vars->wall_top + y, color);
		y++;
	}
}

int	colortoint(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}
