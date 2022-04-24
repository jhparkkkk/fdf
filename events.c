/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 07:58:06 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/24 11:05:06 by jeepark          ###   ########.fr       */
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

int	press_mouse(t_map *map)
{
	destroy_mlx(map->mlx, map);
	exit (0);
}

int	press_key(int keycode, t_map *map)
{
	if (keycode == ESC)
	{
		destroy_mlx(map->mlx, map);
		exit (0);
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
