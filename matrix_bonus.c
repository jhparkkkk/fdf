/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:11:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/05/02 16:45:40 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	is(t_map *map, float *x, float *y, float *z)
{
	float	previous_x;
	float	previous_y;

	*z *= map->zoom;
	*x *= map->zoom;
	*y *= map->zoom;
	*x *= (WIDTH / 2) / map->col;
	*y *= (WIDTH / 2) / map->col;
	previous_x = *x;
	previous_y = *y;
	*x = round((previous_x - previous_y) * cos(map->angle_x));
	*y = round(-(*z) + (previous_x + previous_y) * sin(map->angle_x));
	*x += (WIDTH / 2);
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
			is(map, &map->trix[i][j].x, &map->trix[i][j].y, &map->trix[i][j].z);
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
			map->trix[i][j].color = ((map->trix[i][j].z) * 60 + (int)0xFF5234);
			j++;
		}
		i++;
	}
}