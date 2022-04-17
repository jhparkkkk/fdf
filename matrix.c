/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:11:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/17 18:21:38 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

int scale_x(t_map *map)
{
	int distance;
	(void)map;
	distance = WINDOW_WIDTH / map->col / 2;
	return (distance);	
}

int scale_y(t_map *map)
{
	int distance;
	(void)map;
	distance = WINDOW_HEIGHT / map->row / 2 ;
	return (distance);	
}

void iso(t_map *map, float *x, float *y, float z)
{
    float previous_x;
    float previous_y;
	
	if (map->gap_z)
		z *= map->gap_z;
    previous_x = (*x * scale_x(map)) - ((map->col * scale_x(map)) / 2);
    previous_y = (*y * scale_y(map)) - ((map->row * scale_y(map)) / 2);
    *x = round((previous_x - previous_y) * cos(0.523599) + WINDOW_WIDTH / 2 );
    *y = round(-z + (previous_x + previous_y) * sin(0.523599) + WINDOW_HEIGHT / 2);
}


void matrix_iso(t_map *map)
{
	int i = 0;
	int j = 0;
	
	while (i < map->row)
	{
		j = 0;
		while (j <= map->col)
		{
			iso(map, &map->matrix[i][j].x, &map->matrix[i][j].y , map->matrix[i][j].z);
			j++;
		}
		i++;
	}
}

void matrix_init(t_map *map)
{
	int i; 
	int j; 
	map->matrix = (t_point **)malloc(sizeof(t_point *) * (map->row + 1));
	
	i = 0;
	while (i < map->row)
	{
		map->matrix[i] = malloc(sizeof(t_point) * (map->col + 1));
		j = 0;
		while (j <= map->col)
		{
			map->matrix[i][j].x = j;
			map->matrix[i][j].y = i;
			map->matrix[i][j].z = map->plan[i][j];
			j++;
		}
		i++;
	}
}