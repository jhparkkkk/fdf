/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_iso.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 03:36:26 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/03 03:44:03 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

void	path_1(t_map *map, t_point *a, t_point *b)
{
	
	a->x = WINDOW_WIDTH / 3;
	a->y = 50;
	b->x = a->x + map->tile_width / 2 ;
	b->y = a->y + map->tile_height / 2;
	printf("\nPATH 1\n");
	printf("A->X = %f | A->Y =%f\n", a->x, a->y);
	printf("B->X = %f | B->Y =%f\n", b->x, b->y);
}

void path_2(t_map *map, t_point *tmp, t_point *a, t_point *b)
{
	tmp->x = b->x;                    
	tmp->y = b->y;
	
	b->x = a->x;
	b->y += map->tile_height;
	a->x = tmp->x;
	a->y = tmp->y;
	printf("\nPATH 2\n");
	printf("A->X = %f | A->Y =%f\n", a->x, a->y);
	printf("B->X = %f | B->Y =%f\n", b->x, b->y);
}

void	path_3(t_map *map, t_point *tmp, t_point *a, t_point *b)
{
	tmp->x = a->x;
	tmp->y = a->y; 
	a->x = b->x;
	a->y = b->y;
	b->x -= (map->tile_width / 2);
	b->y = tmp->y + (map->tile_height / 2);
	printf("\nPATH 3\n");
	printf("A->X = %f | A->Y =%f\n", a->x, a->y);
	printf("B->X = %f | B->Y =%f\n", b->x, b->y);
	
}

void	path_4(t_map *map, t_point *tmp, t_point *a, t_point *b)
{
	tmp->x = a->x;
	tmp->y = a->y; 
	a->x = b->x;
	a->y = b->y;
	b->x += (map->tile_width / 2);
	b->y -= map->tile_height;
	printf("\nPATH 4\n");
	printf("A->X = %f | A->Y =%f\n", a->x, a->y);
	printf("B->X = %f | B->Y =%f\n", b->x, b->y);
}

void	next_row(t_map *map, t_point *a, t_point *b)
{
	a->x = b->x;
	a->y = b->y;
	b->x = WINDOW_WIDTH / 3;
	b->y = a->y + map->tile_height; //(map->tile_height / 2);
}

void	try(t_mlx *mlx, t_map *map, t_point *a, t_point *b)
{
	(void)map;
	//int i = 0;
	//int j = 0;
	t_point tmp;
	
	path_1(map, a, b);
	draw_line(mlx, a, b);
	path_2(map, &tmp, a, b);
	draw_line(mlx, a, b);
	path_3(map, &tmp, a, b);
	draw_line(mlx, a, b);
	path_4(map, &tmp, a, b);
	draw_line(mlx, a, b);
}
