/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-03 16:40:51 by fgedeon           #+#    #+#             */
/*   Updated: 2024-07-03 16:40:51 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
