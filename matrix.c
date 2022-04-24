/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:11:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/24 11:46:55 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso(t_map *map, float *x, float *y, float z)
{
	float	prior_x;
	float	prior_y;

	if (map->gap_z)
		z *= map->gap_z;
	prior_x = *x - (map->col * scale_x(map) / 2);
	prior_y = *y - (map->row * scale_y(map) / 2);
	*x = round((prior_x - prior_y) * cos(map->angle_x) + WIDTH / 2);
	*y = round(-z + (prior_x + prior_y) * sin(M_PI / 6) + HEIGHT / 2);
}

void	matrix_iso(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j <= map->col)
		{
			iso(map, &map->trix[i][j].x, &map->trix[i][j].y, map->trix[i][j].z);
			j++;
		}
		i++;
	}
}

void	matrix_init(t_map *map)
{
	int	i;
	int	j;

	map->trix = (t_point **)malloc(sizeof(t_point *) * (map->row + 1));
	i = 0;
	while (i < map->row)
	{
		map->trix[i] = malloc(sizeof(t_point) * (map->col + 1));
		j = 0;
		while (j <= map->col)
		{
			map->trix[i][j].x = find_x(map, j);
			map->trix[i][j].y = find_y(map, i);
			map->trix[i][j].z = map->plan[i][j];
			j++;
		}
		i++;
	}
}
