/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 07:59:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/23 19:18:29 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

void	new_image(t_mlx *mlx, t_map *map)
{
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx->img = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
	draw_map(map, mlx);
}

void	destroy_mlx(t_mlx *mlx, t_map *map)
{
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	free_plan(map->plan);
	matrix_destroy(map);
}

int	ft_mlx_init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (MLX_ERROR);
	mlx->win = mlx_new_window(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (!mlx->win)
		return (free(mlx->ptr), MLX_ERROR);
	mlx->img = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
	mlx->gap_x = 0;
	mlx->gap_y = 0;
	return (0);
}
