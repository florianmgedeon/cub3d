/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:01:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/19 11:03:56 by jkoupy           ###   ########.fr       */
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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;	
}	t_color;

typedef struct s_map
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_color		floor;
	t_color		ceiling;
	int			size_x;
	int			size_y;
	int			**data;
	t_player	player;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	direction;
}	t_player;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	void			*mlx;
	void			*win;
	t_map			map;
}	t_data;

//main.c
int		main(int argc, char **argv);

//parse.c
bool	parse_map(t_data *data, char *file);
bool	manage_line(t_map *map, char *line);
bool	parse_texture(char **path, char *line);
bool	parse_color(t_color *color, char *line);
bool	parse_map_data(t_map *map, char *line);

//parse_utils.c
void	skip_spaces(char *line, int *i);
int		is_player(char c);
void	set_player(t_map *map, int x, int y, char c);

#endif