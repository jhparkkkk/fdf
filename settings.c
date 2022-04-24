/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:21:06 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/24 12:01:14 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_move(t_mlx *mlx, t_map *map, int keycode)
{
	if (keycode == GO_RIGHT)
		mlx->gap_x += 10;
	else if (keycode == GO_LEFT)
		mlx->gap_x -= 10;
	else if (keycode == GO_UP)
		mlx->gap_y -= 10;
	else if (keycode == GO_DOWN)
		mlx->gap_y += 10;
	new_image(mlx, map, keycode);
}

void	set_altitude(t_mlx *mlx, t_map *map, int keycode)
{
	if (keycode == HIGHER)
		map->gap_z += 1;
	else if (keycode == LOWER)
		map->gap_z -= 1;
	new_image(mlx, map, keycode);
}

void	set_zoom(t_mlx *mlx, t_map *map, int keycode)
{
	if (keycode == PLUS && map->zoom < INT_MAX)
		map->zoom += 1;
	if (keycode == MINUS && map->zoom > INT_MIN)
		map->zoom -= 1;
	new_image(mlx, map, keycode);
}

void	set_angle(t_mlx *mlx, t_map *map, int keycode)
{
	if (keycode == ROTATE_RIGHT)
		map->angle_x += 0.1;
	if (keycode == ROTATE_LEFT)
		map->angle_x -= 0.1;
	new_image(mlx, map, keycode);
}
