/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 07:59:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/05/02 14:09:09 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	matrix_destroy(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->row)
	{	
		free(map->trix[i]);
		i++;
	}
	free(map->trix);
}

// void	new_image(t_mlx *mlx, t_map *map, int keycode)
// {
// 	if (keycode == HIGHER || keycode == LOWER
// 		|| keycode == PLUS || keycode == MINUS
// 		|| keycode == ROTATE_RIGHT || keycode == ROTATE_LEFT)
// 	{
// 		matrix_destroy(map);
// 		matrix_init(map);
// 		matrix_iso(map);
// 	}
// 	mlx_destroy_image(mlx->ptr, mlx->img);
// 	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
// 	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
// 	draw_map(map, mlx);
// }

void	destroy_mlx(t_mlx *mlx, t_map *map)
{
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	free_plan(map->plan);
	matrix_destroy(map);
}

void handle_map_error(t_map *map)
{
	free_plan(map->plan);
	write(STDERR_FILENO, "error\n", 6);
	exit(1);
}

int	ft_mlx_init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (MLX_ERROR);
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "fdf");
	if (!mlx->win)
		return (free(mlx->ptr), MLX_ERROR);
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->end);
	mlx->gap_x = 0;
	mlx->gap_y = 0;
	return (0);
}
