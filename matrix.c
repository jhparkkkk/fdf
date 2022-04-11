/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:11:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/11 17:17:49 by jeepark          ###   ########.fr       */
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
	distance =  (WINDOW_WIDTH / 3 ) / 20;
	return (distance);	
}

int scale_y(t_map *map)
{
	int distance;
	(void)map;
	distance = (WINDOW_HEIGHT / 3) / 20 ;
	return (distance);	
}

void iso(t_map *map, float *x, float *y, float z)
{
    float previous_x;
    float previous_y;

	//z *= 10;
    previous_x = *x;
    previous_y = *y;
    *x = round((previous_x - previous_y) * cos(0.523599) * scale_x(map) + WINDOW_WIDTH / 3); //WINDOW_WIDTH / map->col);
    *y = round(-z + (previous_x + previous_y) * sin(0.523599) * scale_y(map) + WINDOW_HEIGHT / 3); //WINDOW_HEIGHT / map->row);
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