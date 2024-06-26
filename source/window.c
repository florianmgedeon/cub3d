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

//changes window when keys are pressed
int	key_hook(int keycode, t_data *data)
{
	if (keycode == 100)//right
		data->test_pos_x += 10;
	if (keycode == 115)//down
		data->test_pos_y += 10;
	if (keycode == 97)//left
		data->test_pos_x -= 10;
	if (keycode == 119)//up
		data->test_pos_y -= 10;
	render(data);
	return (0);
}

//cleans up if window is closed
int	x_the_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	//destroy images with mlx_destroy_image
	mlx_destroy_image(data->mlx, data->test_player);
	//more destroy here

	mlx_destroy_display(data->mlx);
	//free map memory here
	free(data->mlx);
	exit(0);
}

//just for testing
void	put_map(t_data *data)
{
	int i = 0;
	while (i <= 1150) {
		mlx_put_image_to_window(data->mlx, data->win, data->test_wall, i, 0);
		i += 50; }
	i = 0;
	while (i <= 1150) {
		mlx_put_image_to_window(data->mlx, data->win, data->test_wall, i, 550);
		i += 50; }
	i = 0;
	while (i <= 550) {
		mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 0, i);
		i += 50; }
	i = 0;
	while (i <= 550) {
		mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 1150, i);
		i += 50; }
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 50);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 100);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 150);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 200);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 400, 250);
	mlx_put_image_to_window(data->mlx, data->win, data->test_wall, 800, 400);
}

//puts images of the map to the window
void	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);//just for testing
	mlx_put_image_to_window(data->mlx, data->win, data->test_player, data->test_pos_x, data->test_pos_y);
	put_map(data);//just for testing
}

//creates the window & loads files to images
int start_win(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map.size_x, data->map.size_y, "cub3D");
	if (!data->win)
		return (0);
	data->test_player = mlx_xpm_file_to_image(data->mlx, "./textures/test_player.xpm",
			&data->test_height, &data->test_width);
	data->test_wall = mlx_xpm_file_to_image(data->mlx, "./textures/test_wall.xpm",
		&data->test_height, &data->test_width);
    
	return (1);
}
