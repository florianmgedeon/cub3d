/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startwin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:12:25 by fgedeon           #+#    #+#             */
/*   Updated: 2024/07/03 17:06:54 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// creates the window & loads files to images
int	start_win(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map.size_x
			* data->map.tile_size, data->map.size_y * data->map.tile_size,
			"cub3D");
	if (!data->win)
		return (0);
	data->test_player = mlx_xpm_file_to_image(data->mlx,
			"./textures/test_player.xpm", &data->test_height,
			&data->test_width);
	data->test_wall = mlx_xpm_file_to_image(data->mlx,
			"./textures/test_wall.xpm", &data->test_height, &data->test_width);
	return (1);
}

int	*save_texture(t_data *data, char *path)
{
	t_tex	tex_info;

	tex_info.tex = TEXTURE_SIZE;
	tex_info.tex_ptr = mlx_xpm_file_to_image(data->mlx, path,
			&tex_info.tex, &tex_info.tex);
	tex_info.texture = (int *)mlx_get_data_addr(tex_info.tex_ptr,
			&tex_info.bits_per_pixel,
			&tex_info.line_length, &tex_info.endian);
	return (tex_info.texture);
}

// new window for 3D - malloc NEEDS A FREE LATER
//save texture file to image then image to address function
int	start_win2(t_data *data)
{
	data->win2 = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"cub3D");
	if (!data->win2)
		return (0);
	data->texture = malloc(sizeof(int *) * 4);
	if (!data->texture)
		return (0);
	data->texture[NORTH] = save_texture(data, data->map.no_path);
	data->texture[SOUTH] = save_texture(data, data->map.so_path);
	data->texture[WEST] = save_texture(data, data->map.we_path);
	data->texture[EAST] = save_texture(data, data->map.ea_path);
	if (!data->texture[NORTH] || !data->texture[SOUTH] || !data->texture[WEST]
		|| !data->texture[EAST])
		return (0);
	return (1);
}

int	colortoint(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}
