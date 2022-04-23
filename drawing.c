/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/23 17:19:39 by jeepark          ###   ########.fr       */
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

	if (x < 0 || y < 0 || x > WINDOW_WIDTH - 1 || y > WINDOW_HEIGHT)
		return ;
	pix = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	*(int *)pix = color;
}

void	draw_line(t_mlx *mlx, t_point *a, t_point *b)
{
	t_bres	bres;

	bres.end = *b;
	bres.start = *a;
	check_movement(mlx, &bres.start, &bres.end);
	bres.distance.x = f_abs(bres.end.x - bres.start.x);
	bres.distance.y = -f_abs(bres.end.y - bres.start.y);
	bres.error_0 = bres.distance.x + bres.distance.y;
	find_sign(a, b, &bres.sign);
	while (bres.start.x != bres.end.x || bres.start.y != bres.end.y)
	{
		put_pix(mlx, bres.start.x, bres.start.y, 0xFFCCCC);
		bres.error_1 = 2 * bres.error_0;
		if (bres.error_1 >= bres.distance.y)
		{
			bres.error_0 += bres.distance.y;
			bres.start.x += bres.sign.x;
		}
		if (bres.error_1 <= bres.distance.x)
		{
			bres.error_0 += bres.distance.x;
			bres.start.y += bres.sign.y;
		}
	}
}

void	draw_map(t_map *map, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
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
