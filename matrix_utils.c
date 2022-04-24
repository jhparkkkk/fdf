/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:44:33 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/24 11:56:55 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	scale_x(t_map *map)
{
	float	scale_x;

	scale_x = (WIDTH / map->col / 2) + map->zoom;
	return (scale_x);
}

float	scale_y(t_map *map)
{
	float	scale_y;

	scale_y = (HEIGHT / map->row / 2) + map->zoom;
	return (scale_y);
}

float	find_x(t_map *map, int j)
{
	float	x;

	x = j * scale_x(map) - ((map->col * scale_x(map)) / 2) + WIDTH / 2;
	return (x);
}

float	find_y(t_map *map, int i)
{
	float	y;

	y = i * scale_y(map) - ((map->row * scale_y(map)) / 2) + HEIGHT / 2;
	return (y);
}
