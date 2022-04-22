/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/22 17:29:37 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

void	put_pix(t_mlx *mlx, int x, int y, int color)
{
	char	*pix;

	if (x < 0 || y < 0 || x > WINDOW_WIDTH - 1 || y > WINDOW_HEIGHT - 1)
		return ;
	pix = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	*(int *)pix = color; 
}

void	draw_line(t_mlx *mlx, t_point *a, t_point *b)
{
	t_point distance;
	t_point sign;
	int		error[2];
	t_point	start;
	t_point	end; 

	end.x = b->x;
	end.y = b->y; 
	start.x = a->x;
	start.y = a->y;
	check_movement(mlx, &start, &end);
	distance.x = f_abs(end.x - start.x);
	distance.y = -f_abs(end.y - start.y);
	error[0] = distance.x + distance.y;
	find_sign(a, b, &sign);
	
	while (start.x != end.x || start.y != end.y)
	{
		put_pix(mlx, start.x, start.y, 0xFFCCCC);
		error[1] = 2 * error[0];
      	if (error[1] >= distance.y)
	  	{
			  error[0] += distance.y;
			  start.x += sign.x; 
		} 
    	if (error[1] <= distance.x) 
	  	{
			  error[0] += distance.x;
			  start.y += sign.y;
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
				draw_line(mlx, &map->matrix[i][j], &map->matrix[i + 1][j]);
			if (j + 1 <= map->col)
				draw_line(mlx, &map->matrix[i][j], &map->matrix[i][j + 1]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}