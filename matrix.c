/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:11:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/30 19:31:55 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void    iso(t_point *coord, int lines, int map->col)
void	iso(t_map *map, float *x, float *y, float *z)
{
    double    previous_x;
    double    previous_y;

	if (map->gap_z)
	{
		printf("%f\n", *z);
		*z *= map->gap_z;
		map->flag = 1;
	}
	*x *= 10 + map->zoom;
	*y *= 10 + map->zoom;
    previous_x = *x;
    previous_y = *y;
    *x = round((previous_x - previous_y) * cos(map->angle_x));
    *y = round(-(*z) + (previous_x + previous_y) * sin(map->angle_x));
	//*z = round(*z);
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
			map->trix[i][j].z = map->plan[i][j];
			map->trix[i][j].color = ((map->trix[i][j].z) * 40 + (int)0xFF5733);
			j++;
		}
		i++;
	}
}
