/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-26 11:38:29 by fgedeon           #+#    #+#             */
/*   Updated: 2024-06-26 11:38:29 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//cleans up if window is closed
int	x_the_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	//destroy images with mlx_destroy_image
	mlx_destroy_display(data->mlx);
	//free map memory here
	free(data->mlx);
	exit(0);
}

//puts images of the map to the window
void	render(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->test_player, 600, 300);
}

//creates the window & loads files to images
int start_win(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map.size_x, data->map.size_y, "cub3D");
	if (!data->win)
		return (0);
	data->test_player = mlx_xpm_file_to_image(data->mlx, "./textures/test_player.xpm",
			&data->test_height, &data->test_width);
    
	return (1);
}