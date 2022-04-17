/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 07:58:06 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/17 16:18:08 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

int handle_no_event(void *mlx)
{
	(void)*mlx;
	return (0);
}

void	move_map(t_mlx *mlx, t_map *map, int keycode)
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

int	handle_input(int keycode, t_map *map)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(map->mlx->ptr, map->mlx->win);
		mlx_destroy_image(map->mlx->ptr, map->mlx->img);
		free(map->mlx->ptr);
		exit(1);
	}
	if (keycode == GO_RIGHT || keycode == GO_LEFT || keycode == GO_UP || keycode == GO_DOWN) // move to right 
	{
		move_map(map->mlx, map, keycode);
	}
	draw_map(map, map->mlx);
	return (0);
}


/* Si la touche symbole correspond bien a ESC, je ferme la fenetre.
int	handle_input(int keycode, t_mlx **mlx, t_map *map)
{
	//printf pour test
	if (keycode == ESC)
	{
		mlx_destroy_window((*mlx)->ptr, (*mlx)->win);
		mlx_destroy_image((*mlx)->ptr, (*mlx)->img);
		free((*mlx)->ptr);
		exit(1);
	}
	if (keycode == GO_RIGHT || keycode == GO_LEFT || keycode == GO_UP || keycode == GO_DOWN) // move to right 
	{
		move_map(mlx, map, keycode);
	}
	return (0);
}*/
