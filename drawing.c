/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/05/02 07:30:31 by jeepark          ###   ########.fr       */
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

	if (x < 0 || y < 0 || x > WIDTH - 1 || y > HEIGHT)
		return ;
	pix = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	*(int *)pix = color;
}

void	draw_line(t_mlx *mlx, t_point *a, t_point *b)
{
	t_bres	br;

	br.end = *b;
	br.start = *a;
	check_movement(mlx, &br.start, &br.end);
	br.distance.x = f_abs(br.end.x - br.start.x);
	br.distance.y = -f_abs(br.end.y - br.start.y);
	br.error_0 = br.distance.x + br.distance.y;
	find_sign(a, b, &br.sign);
	while (br.start.x != br.end.x || br.start.y != br.end.y)
	{
		put_pix(mlx, br.start.x, br.start.y, br.start.color);
		br.error_1 = 2 * br.error_0;
		if (br.error_1 >= br.distance.y)
		{
			br.error_0 += br.distance.y;
			br.start.x += br.sign.x;
		}
		if (br.error_1 <= br.distance.x)
		{
			br.error_0 += br.distance.x;
			br.start.y += br.sign.y;
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
				draw_line(mlx, &map->trix[i][j], &map->trix[i + 1][j]);
			if (j + 1 <= map->col)
				draw_line(mlx, &map->trix[i][j], &map->trix[i][j + 1]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}
