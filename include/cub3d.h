/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:01:06 by jkoupy            #+#    #+#             */
/*   Updated: 2024/06/18 15:07:31 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;	
}	t_color;

typedef struct s_map
{
	char		*name;
	char		*path;
	int			size_x;
	int			size_y;
	int			**data;
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
	t_map			map;
}	t_data;

#endif