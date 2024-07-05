/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:40:51 by fgedeon           #+#    #+#             */
/*   Updated: 2024/07/04 21:55:54 by jkoupy           ###   ########.fr       */
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

// calculates the x and y of the texture to draw in the wall
void	draw_texture(t_data *data, t_ray *vars, int colx)
{
	int	x;
	int	y;
	int	tex_y;
	int	color;

	y = 0;
	while (vars->drawstart + y < vars->drawend)
	{
		if (vars->drawstart + y < 0)
		{
			y++;
			continue ;
		}
		if (vars->drawstart + y >= SCREEN_HEIGHT)
			break ;
		x = (int)((vars->x_of_tex - (int)vars->x_of_tex) * TEXTURE_SIZE);
		if (vars->tex == SOUTH || vars->tex == WEST)
			x = TEXTURE_SIZE - x - 1;
		tex_y = (y * TEXTURE_SIZE) / (vars->drawend - vars->drawstart);
		color = data->texture[vars->tex][x + tex_y * TEXTURE_SIZE];
		mlx_pixel_put(data->mlx, data->win2, colx, vars->drawstart + y, color);
		y++;
	}
}

int	colortoint(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}
