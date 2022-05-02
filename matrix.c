/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:11:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/05/02 11:57:59 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso(t_map *map, float *x, float *y, float *z)
{
    double    previous_x;
    double    previous_y;

	*z *= map->zoom;
	*x *= map->zoom;
	*y *= map->zoom;
	*x *= 10;
	*y *= 10;
    previous_x = *x;
    previous_y = *y;
    *x = round((previous_x - previous_y) * cos(map->angle_x));
    *y = round(-(*z) + (previous_x + previous_y) * sin(map->angle_x));
	*x = *x + WIDTH / 2;
    *y = *y + HEIGHT / 2;
   
}

void	parallel(t_map *map, float *x, float *y, float *z)
{
	(void)z;
	(void)map;
	
	*x *= 10 + map->zoom;
	*y *= 10 + map->zoom;
	*x = *x + WIDTH / 2;
    *y = *y + HEIGHT / 2;
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
			iso(map, &map->trix[i][j].x, &map->trix[i][j].y, &map->trix[i][j].z);
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
			map->trix[i][j].x = j;
			map->trix[i][j].y = i;
			map->trix[i][j].z = map->plan[i][j] * map->gap_z;
			map->trix[i][j].color = (int)0xFBBEB1;
			j++;
		}
		i++;
	}
}