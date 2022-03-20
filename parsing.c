/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/03/20 20:34:28 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"


// j'initialise la minilibx --> il s'agit d'un pointeur sur une structure
//contenant tous les outils graphiques dont j'ai besoin.


void	ft_mlx_destroy(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_image(mlx->ptr, mlx->img);
	free(mlx->ptr);
}

int handle_no_event(void *mlx)
{
	(void)*mlx;
	return (0);
}

// Si la touche symbole correspond bien a ESC, je ferme la fenetre.
int	handle_input(int keycode, t_mlx *mlx)
{
	//printf pour test
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		exit(1); // comment shut le prog ? 
	}
	return (0);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*s;

	s = mlx->addr + (y * mlx->size_line + x * (mlx->bits_per_pixel / 8));
	
	*(unsigned int*)s = color;
	
}

void	drawing(t_mlx *mlx, t_map *map)
{
	int distance_x;
	int distance_y;
	int x;
	int y;
	int p;
	
	distance_x = (map->x + 100) - map->x;
	distance_y = (map->y + 0) - map->y;
	x = map->x;
	y = map->y;
	p = 2 * distance_y - distance_x;
	while(x <= map->x + 100)
	{
		put_pixel(mlx, x, y, (int)0xFF00FF0000);
		x++;
		if (p < 0)
			p = p + 2 * distance_y - 2;
		else
		{
			p = p + 2 * distance_y - 2 * distance_x;
			y++;
		}
	}
}


int ft_mlx_init(t_mlx *mlx, t_map *map)
{
	//int x = 0;
	//int y = 0;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (MLX_ERROR);
	mlx->win = mlx_new_window(mlx->ptr,  WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (!mlx->win)
		return (free(mlx->win), MLX_ERROR);
	mlx->img = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->size_line,
								&mlx->endian);
	//mlx_loop_hook(mlx->ptr, &drawing, &mlx);
	//mlx_pixel_put(mlx->ptr, mlx->win, 5, 5, 0xFF00FF00);
	//drawing(mlx, 100, 100, 0x00FF0000);
	/*while (x < 300)
	{
		drawing(mlx, x++, y, 0x00FF0000);
	}*/
	//print(mlx, map, x, y);
	drawing(mlx, map);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	mlx_loop_hook(mlx->ptr, &handle_no_event, &mlx);
	mlx_key_hook(mlx->win, &handle_input, &mlx);
	mlx_loop(mlx->ptr);
	return (0);
}



int	main(int ac, char **av)
{
	int i = 0;
	int j = 0;
	t_map	map;
	t_mlx	mlx;
	if (ac < 2)
		return (0);
	read_map(av, &map);
	while(i < map.row)
	{
		j = 0;
		printf("\n");
		while(j < map.col)
		{
			printf("%d", map.plan[i][j]);
			j++;
		}
		i++;
	}
	map.x = 10;
	map.y = 10;
	ft_mlx_init(&mlx, &map);
	if (ft_mlx_init(&mlx, &map) == MLX_ERROR)
		return (0);
	
	//drawing(&mlx, 100, 100, 0x00FF0000);
	//mlx_loop_hook(mlx.ptr, &drawing, &mlx);
	//mlx.img = mlx_new_image(mlx.ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	

    //img.img = mlx_new_image(mlx.ptr, 1920, 1080);
	//mlx.img = mlx_get_data_addr(mlx.img, mlx.bits_per_pixel, mlx.size_line, mlx.endian);
	
	/*j = 0;
	while(i < 100)
	{
		mlx_pixel_put(mlx.ptr, mlx.win, j, i, 0xFF00FF00);
		j++;
		i++;
	}*/
	return (0);
}
