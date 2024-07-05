/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startwin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:12:25 by fgedeon           #+#    #+#             */
/*   Updated: 2024/07/04 21:58:30 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	*save_texture(t_data *data, char *path)
{
	t_tex	tex_info;
	int		*temp;
	int		i;

	tex_info.tex = TEXTURE_SIZE;
	tex_info.tex_ptr = mlx_xpm_file_to_image(data->mlx, path,
			&tex_info.tex, &tex_info.tex);
	if (tex_info.tex_ptr == NULL)
		return (0);
	temp = (int *)mlx_get_data_addr(tex_info.tex_ptr,
			&tex_info.bits_per_pixel,
			&tex_info.line_length, &tex_info.endian);
	if (temp == NULL)
		return (mlx_destroy_image(data->mlx, tex_info.tex_ptr), NULL);
	tex_info.texture = malloc(sizeof(int) * tex_info.tex * tex_info.tex);
	if (!tex_info.texture)
		return (mlx_destroy_image(data->mlx, tex_info.tex_ptr), NULL);
	i = 0;
	while (i < tex_info.tex * tex_info.tex)
	{
		tex_info.texture[i] = temp[i];
		i++;
	}
	mlx_destroy_image(data->mlx, tex_info.tex_ptr);
	return (tex_info.texture);
}

// new window for 3D - malloc NEEDS A FREE LATER
//save texture file to image then image to address function
int	start_win(t_data *data)
{
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"cub3D");
	if (!data->win)
		return (0);
	data->texture = malloc(sizeof(int *) * 4);
	if (!data->texture)
		return (mlx_destroy_window(data->mlx, data->win), 0);
	data->texture[NORTH] = save_texture(data, data->map.no_path);
	data->texture[SOUTH] = save_texture(data, data->map.so_path);
	data->texture[WEST] = save_texture(data, data->map.we_path);
	data->texture[EAST] = save_texture(data, data->map.ea_path);
	if (!data->texture[NORTH] || !data->texture[SOUTH] || !data->texture[WEST]
		|| !data->texture[EAST])
		return (0);
	return (1);
}
