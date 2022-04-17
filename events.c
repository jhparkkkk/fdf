/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 07:58:06 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/17 18:22:33 by jeepark          ###   ########.fr       */
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
	if (keycode == 1)
	{
		map->gap_z += 1;
		printf("COUCOU\n");
		matrix_init(map);
		matrix_iso(map);
	}	
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
	if (keycode == GO_RIGHT || keycode == GO_LEFT || keycode == GO_UP || keycode == GO_DOWN)
		set_move(map->mlx, map, keycode);
	if (keycode == 1)
		set_altitude(map->mlx, map, keycode);
	//draw_map(map, map->mlx);
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
