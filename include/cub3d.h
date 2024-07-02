/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:01:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/07/02 17:26:03 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//keys
# define LEFT 123
# define RIGHT 124
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define PI 3.14159265359
# define SCREEN_WIDTH 1500
# define SCREEN_HEIGHT 800
# define NBR_RAYS (SCREEN_WIDTH / 1)
# define TEXTURE_SIZE 64
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# include "../library/libft/include/libft.h"
# include "../library/get_next_line/include/get_next_line.h"

# include <fcntl.h>		//open, close
# include <unistd.h> 	//read, write
# include <stdio.h> 	//printf, perror
# include <stdlib.h> 	//malloc, free, exit
# include <errno.h> 	//strerror
# include <sys/time.h>  //gettimeofday
# include <math.h> 		//math library
# include <mlx.h> 		//MinilibX
# include <stdbool.h> 	//bool
# include <stdbool.h> 	//bool


typedef struct s_color
{
	int	r;
	int	g;
	int	b;	
}	t_color;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_player;

typedef struct s_map
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_color		floor;
	t_color		ceiling;
	int			tile_size;
	int			size_x;
	int			size_y;
	int			**data;
	int 		**textures;
	t_player	player;
}	t_map;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	void			*mlx;
	void			*win;
	void			*win2;
	t_map			map;
	void			*test_player;//just for testing
	void			*test_wall;//just for testing
	int				test_height;//just for testing
	int				test_width;//just for testing
}	t_data;

//check.c
bool	map_check(t_map map);
bool	null_check(t_map map);
bool	color_check(t_map map);
bool	valid_map_check(t_map map);
bool	load_textures(t_data *data);

//init.c
void	init_data(t_data *data);
void	init_player(t_player *player);
void	set_dir(t_player *player, char c);
void	set_plane(t_player *player, char c);
void	init_colors(t_map *map);
int		free_data(t_data *data);

//main.c
int		main(int argc, char **argv);
bool	parse(t_data *data, char *file);

//parsing.c
bool	manage_line(t_map *map, char *line);
bool	parse_texture(char **path, char *line);
bool	parse_color(t_color *color, char *line);
bool	parse_map_data(t_map *map, char *line);
void	update_map_size(t_map *map, int x);

//parse_utils.c
void	skip_spaces(char *line, int *i);
int		is_player(char c);
bool	set_player(t_map *map, int x, char c);
bool	arg_check(int argc, char **argv);
int		**map_add_line(t_map *map, int *new_line);

//print.c
void	print_map(t_map map);
void	print_line(int *line, int size);

//window.c
int		start_win(t_data *data);
int		start_win2(t_data *data);
void	render(t_data *data);
int		x_the_win(t_data *data);
int		key_hook(int keycode, t_data *data);

#endif