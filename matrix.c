/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:11:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/23 18:45:50 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	scale_x(t_map *map)
{
	float	scale_x;

	scale_x = (WINDOW_WIDTH / map->col / 2) + map->zoom;
	return (scale_x);
}

static float	scale_y(t_map *map)
{
	float	scale_y;

	scale_y = (WINDOW_HEIGHT / map->row / 2) + map->zoom;
	return (scale_y);
}

void	iso(t_map *map, float *x, float *y, float z)
{
	float	prior_x;
	float	prior_y;

	if (map->gap_z)
		z *= map->gap_z;
	prior_x = *x - (map->col * scale_x(map) / 2);
	prior_y = *y - (map->row * scale_y(map) / 2);
	*x = round((prior_x - prior_y) * cos(map->angle_x) + WINDOW_WIDTH / 2);
	*y = round(-z + (prior_x + prior_y) * sin(M_PI / 6) + WINDOW_HEIGHT / 2);
}

void	matrix_iso(t_map *map)
{
	int i;
	int j;
	
	i = 0;
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

void matrix_destroy(t_map *map)
{
	int i;

	i = 0;
	while (i < map->row)
	{	
		free(map->matrix[i]);
		i++;
	}
	free(map->matrix);
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
			map->matrix[i][j].x = j * scale_x(map) - ((map->col * scale_x(map)) / 2) + WINDOW_WIDTH / 2;
			map->matrix[i][j].y = i * scale_y(map) - ((map->row * scale_y(map)) / 2) + WINDOW_HEIGHT / 2;
			map->matrix[i][j].z = map->plan[i][j];
			j++;
		}
		i++;
	}
}

