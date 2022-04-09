/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/09 19:15:56 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*pix;
	
	if ( x < 0 || y < 0 || x > WINDOW_WIDTH - 1 || y > WINDOW_HEIGHT)
		return ; 
	printf("x = %d | y = %d \n", x, y);
	pix = mlx->addr + (y * mlx->size_line + x * (mlx->bits_per_pixel / 8));
	*(int *)pix = color;
	
}

void draw_line(t_mlx *mlx, int ax, int ay, int bx, int by)  
{

	int dx =  abs(bx - ax), sx = ax < bx ? 1 : -1;
	int dy = -abs(by - ay), sy = ay < by ? 1 : -1; 
	int err = dx+dy, e2; /* error value e_xy */
	while (1)
	{
		put_pixel(mlx, ax, ay, 0xFF0000);
		if (ax == bx && ay == by) 
			break;
		e2 = 2 * err;
      	if (e2 >= dy)
	  	{
			  err += dy;
			  ax += sx; 
		} /* e_xy+e_x > 0 */
    	if (e2 <= dx) 
	  	{
			  err += dx;
			  ay += sy;
		} /* e_xy+e_y < 0 */
   }
}


 void iso(float *x, float *y, float z)
{
    float previous_x;
    float previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = round((previous_x - previous_y) * cos(0.523599) * 20 + WINDOW_WIDTH / 2);
    *y = round(-z + (previous_x + previous_y) * sin(0.523599) * 40 + WINDOW_HEIGHT / 3);
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

void matrix_iso(t_map *map)
{
	int i = 0;
	int j = 0;
	
	while (i < map->row)
	{
		j = 0;
		while (j <= map->col)
		{
			iso(&map->matrix[i][j].x, &map->matrix[i][j].y , map->matrix[i][j].z);
			j++;
		}
		i++;
	}
}



void	draw_map(t_map *map, t_mlx *mlx)
{
	int i = 0;
	int j = 0;
	
	printf("map.matrix[%d][%d].x = %f\n", i, j, map->matrix[i][j].x);
	draw_line(mlx, map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i + 1][j].x, map->matrix[i + 1][j].y);
	/*while (i < map->row)
	{
		j = 0;
		while (j < map->col)
		{
			if (i + 1 < map->row)
				draw_line(mlx, map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i + 1][j].x, map->matrix[i + 1][j].y);
			j++;
		}
		i++;
	}*/
}


int	main(int ac, char **av)
{
	int i = 0;
	int j = 0;
	t_map	map;
	t_mlx	mlx;

	if (ac < 2)
		return (0);
	read_map(av, &map);
	printf("COLUMNS = %d | LINES = %d\n", map.col, map.row);
	while(i < map.row)
	{
		//printf("\nI = %d | J = %d\n", i, j);
		j = 0;
		printf("\n");
		while(j <= map.col)
		{
			printf("%d ", map.plan[i][j]);
			j++;
		}
		i++;
	}
	matrix_init(&map);
	i = 0;
	while(i < map.row)
	{
		//printf("\nI = %d | J = %d\n", i, j);
		j = 0;
		while(j <= map.col)
		{
			printf("\nmap.matrix[%d][%d].x = %f | .y = %f\n", i, j, map.matrix[i][j].x, map.matrix[i][j].y);
			j++;
		}
		i++;
	}
	matrix_iso(&map);
	//printf("map.matrix[i][j].x = %f\n", map.matrix[0][5].x);
	i = 0;
	while(i < map.row)
	{
		//printf("\nI = %d | J = %d\n", i, j);
		j = 0;
		while(j <= map.col)
		{
			printf("map.matrix[%d][%d].x = %f | .y = %f\n", i, j, map.matrix[i][j].x, map.matrix[i][j].y);
			j++;
		}
		i++;
	}
	map.tile_width = 40;
	map.tile_height = 20;
	ft_mlx_init(&mlx, &map);
	//if (ft_mlx_init(&mlx, &map) == MLX_ERROR)
	//	return (0);
	return (0);
}