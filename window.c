/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 07:59:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/09 19:14:26 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

void	ft_mlx_destroy(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_image(mlx->ptr, mlx->img);
	free(mlx->ptr);
}

int ft_mlx_init(t_mlx *mlx, t_map *map)
{
	(void)map;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (MLX_ERROR);
	mlx->win = mlx_new_window(mlx->ptr,  WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (!mlx->win)
		return (free(mlx->win), MLX_ERROR);
	mlx->img = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
	draw_map(map, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	
	mlx_loop_hook(mlx->ptr, &handle_no_event, &mlx);
	mlx_key_hook(mlx->win, &handle_input, &mlx);
	mlx_loop(mlx->ptr);
	return (0);
}

