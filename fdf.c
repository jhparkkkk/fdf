/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:03:04 by jeepark           #+#    #+#             */
/*   Updated: 2022/05/02 16:20:54 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx;

	if (ac < 2)
		return (0);
	check_extension(av);
	map_init(&map);
	read_map(av, &map);
	matrix_init(&map);
	matrix_iso(&map);
	if (ft_mlx_init(&mlx) == MLX_ERROR)
		return (destroy_mlx(&mlx, &map), 0);
	map.mlx = &mlx;
	draw_map(&map, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, press_key, &map);
	mlx_hook(mlx.win, 17, 1L << 17, press_mouse, &map);
	mlx_loop(mlx.ptr);
	return (0);
}
