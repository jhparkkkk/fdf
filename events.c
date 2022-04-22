/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 07:58:06 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/22 16:43:42 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

int	handle_no_event(void *mlx)
{
	(void)*mlx;
	return (0);
}

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
	new_image(mlx, map);
}

void	set_altitude(t_mlx *mlx, t_map *map, int keycode)
{
	if (keycode == HIGHER)
		map->gap_z += 1;
	else if (keycode == LOWER)
		map->gap_z -= 1;
	matrix_init(map);
	matrix_iso(map);
	new_image(mlx, map);
}

void	set_zoom(t_mlx *mlx, t_map *map, int keycode)
{
	if (keycode == PLUS)
		map->zoom += 1;
	if (keycode == MINUS)
		map->zoom -= 1;
	matrix_init(map);
	matrix_iso(map);
	new_image(mlx, map);
}

void	set_angle(t_mlx *mlx, t_map *map, int keycode)
{
	if (keycode == ROTATE_RIGHT)
		map->angle_x += 0.1;
	if (keycode == ROTATE_LEFT)
		map->angle_x -= 0.1;
	matrix_init(map);
	matrix_iso(map);
	new_image(mlx, map);
}

int	press_key(int keycode, t_map *map)
{
	if (keycode == ESC)
	{
		destroy_mlx(map->mlx);
		exit (1);
	}
	if (keycode == GO_RIGHT || keycode == GO_LEFT
		|| keycode == GO_UP || keycode == GO_DOWN)
		set_move(map->mlx, map, keycode);
	if (keycode == HIGHER || keycode == LOWER)
		set_altitude(map->mlx, map, keycode);
	if (keycode == PLUS || keycode == MINUS)
		set_zoom(map->mlx, map, keycode);
	if (keycode == ROTATE_RIGHT || keycode == ROTATE_LEFT)
		set_angle(map->mlx, map, keycode);
	return (0);
}
