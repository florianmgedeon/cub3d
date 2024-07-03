/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:01:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/07/03 11:44:20 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// keys
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
# define NBR_RAYS SCREEN_WIDTH
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define TEXTURE_SIZE 64

# include "../library/get_next_line/include/get_next_line.h"
# include "../library/libft/include/libft.h"
# include <errno.h>    //strerror
# include <fcntl.h>    //open, close
# include <math.h>     //math library
# include <mlx.h>      //MinilibX
# include <stdbool.h>  //bool
# include <stdio.h>    //printf, perror
# include <stdlib.h>   //malloc, free, exit
# include <sys/time.h> //gettimeofday
# include <unistd.h>   //read, write

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_player
{
	float		x;
	float		y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
}				t_player;

typedef struct s_map
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_color		floor;
	t_color		ceiling;
	int			tile_size; // fust for testing
	int			size_x;
	int			size_y;
	int			**data;
	t_player	player;
}				t_map;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*win;
	void		*win2;
	t_map		map;
	int			**texture;
	void		*test_player;//just for testing
	void		*test_wall;//just for testing
	int			test_height;//just for testing
	int			test_width;//just for testing
}				t_data;

typedef struct s_ray
{
	int			i;
	int			w;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	float		perpwalldist;
	int			tex;
	int			h;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			color_wall;
	int			x_of_tex;
}				t_ray;

// check.c
bool			map_check(t_map map);
bool			null_check(t_map map);
bool			color_check(t_map map);
bool			valid_map_check(t_map map);

// init.c
void			init_data(t_data *data);
void			init_player(t_player *player);
void			set_dir(t_player *player, char c);
void			set_plane(t_player *player, char c);
void			init_colors(t_map *map);
int				free_data(t_data *data);

// main.c
int				main(int argc, char **argv);
bool			parse(t_data *data, char *file);

// parsing.c
bool			manage_line(t_map *map, char *line);
bool			parse_texture(char **path, char *line);
bool			parse_color(t_color *color, char *line);
bool			parse_map_data(t_map *map, char *line);
void			update_map_size(t_map *map, int x);

// parse_utils.c
void			skip_spaces(char *line, int *i);
int				is_player(char c);
bool			set_player(t_map *map, int x, char c);
bool			arg_check(int argc, char **argv);
int				**map_add_line(t_map *map, int *new_line);

// print.c
void			print_map(t_map map);
void			print_line(int *line, int size);

// window.c
int				key_hook(int keycode, t_data *data);
void			calc_ray(t_data *data);

// keyhook.c
void			move_ws(int keycode, t_data *data, float move_speed);
void			move_ad(int keycode, t_data *data, float move_speed);
void			rota(int keycode, t_data *d, float o_dir_x, float o_pl_x);
int				x_the_win(t_data *data);

// startwin.c
int				start_win(t_data *data);
int				start_win2(t_data *data);
int				colortoint(t_color color);

//calc_ray_utils.c
void			init_ray_vars(t_data *data, t_ray *vars);
void			calc_step_side(t_ray *vars, t_data *data);
void			calculate_hit(t_ray *vars, t_data *data);
void			perpdist_and_put_ray(t_data *data, t_ray *vars);
void			calculate_wall_properties(t_ray *vars);

// justfortesting.c REMOVE BEFORE SUBMISSION
void			put_map(t_data *data);
void			put_ray(t_data *data, int color, float end_x, float end_y);

#endif