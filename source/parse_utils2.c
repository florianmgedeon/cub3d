/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-03 16:04:31 by fgedeon           #+#    #+#             */
/*   Updated: 2024-07-03 16:04:31 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//skip spaces in a string and update the i
void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

//check if a char is a player
int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}
