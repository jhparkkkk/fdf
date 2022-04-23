/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:03:04 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/23 20:28:55 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
# include <math.h>

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx;

	if (ac < 2)
		return (0);
	map.angle_x = M_PI / 6;
	read_map(av, &map);
	matrix_init(&map);
	matrix_iso(&map);
	if (ft_mlx_init(&mlx) == MLX_ERROR)
		return (destroy_mlx(&mlx, &map), 0);
	map.mlx = &mlx;
	draw_map(&map, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, press_key, &map);
	mlx_loop(mlx.ptr);
	destroy_mlx(&mlx, &map);
	free_plan(map.plan);
	matrix_destroy(&map);
	return (0);
}