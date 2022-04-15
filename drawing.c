/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/15 10:32:40 by jeepark          ###   ########.fr       */
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
	
	if ( x < 0 || y < 0 || x > WINDOW_WIDTH - 1 || y > WINDOW_HEIGHT - 1)
		return ; 
	pix = mlx->addr + (y * mlx->size_line + x * (mlx->bits_per_pixel / 8));
	*(int *)pix = color;
	
}

float f_abs(float nb)
{
	if (nb < 0)
		return (nb *= -1);
	return (nb);
}

void	find_sign(float ax, float ay, float bx, float by, t_point *sign)
{
	if (ax < bx)
		sign->x = 1;
	else
		sign->x = -1;

	if (ay < by)
		sign->y = 1;
	else
		sign->y = -1;
}

void draw_line(t_mlx *mlx, float ax, float ay, float bx, float by)  
{
	t_point distance;
	t_point sign;
	int		error[2];
	
	distance.x = f_abs(bx - ax);
	distance.y = -f_abs(by - ay);
	error[0] = distance.x + distance.y;
	find_sign(ax, ay, bx, by, &sign);
	
	while (ax != bx || ay != by)
	{
		put_pixel(mlx, ax, ay, 0xFFCCCC);
		error[1] = 2 * error[0];
      	if (error[1] > distance.y)
	  	{
			  error[0] += distance.y;
			  ax += sign.x; 
		} 
    	if (error[1] < distance.x) 
	  	{
			  error[0] += distance.x;
			  ay += sign.y;
		}
   }
}



void	draw_map(t_map *map, t_mlx *mlx)
{
	int i = 0;
	int j = 0;
	
	while (i < map->row)
	{
		j = 0;
		while (j <= map->col)
		{
			if (i + 1 < map->row)
				draw_line(mlx, map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i + 1][j].x, map->matrix[i + 1][j].y);
			if (j + 1 <= map->col)
				draw_line(mlx, map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i][j + 1].x, map->matrix[i][j + 1].y);
			j++;
		}
		i++;
	}
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
		j = 0;
		printf("\n");
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