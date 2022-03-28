/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/03/28 19:12:38 by jeepark          ###   ########.fr       */
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

void	put_pixel(t_mlx *mlx, float x, float y, int color)
{
	char	*pix;
	
	pix = mlx->addr + ((int)y * mlx->size_line + (int)x * (mlx->bits_per_pixel / 8));
	*(int *)pix = color;
	
}

void	put_height(t_map *map, int x, int y)
{
	x = (x - y) * cos(0.523599);
	y = (x + y) * sin(0.523599) - map->plan[y][x];
}	

void draw_line(t_mlx *mlx, float x0, float y0, float x1, float y1)  
{
	int dx =  fabs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = -fabs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = dx+dy, e2; /* error value e_xy */
	
	for(;;){  /* loop */
      put_pixel(mlx, x0,y0, 0xFF0000);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}

void	draw_map(t_mlx *mlx, t_map *map)
{
	int i = 0;
	int j = 0;
	float x0 = WINDOW_WIDTH / 3; //10;
	float y0= WINDOW_HEIGHT / 3; //10;
	float x1 = 20;
	float y1 = 10;
	int tmp_x = 0;
	int tmp_y = 0;

	printf("\ncolumns = %d\n", map->col);
	printf("\nrow = %d\n", map->row);
	while (i <= map->row)
	{
		j = -1;
		while(j++ < map->col - 1)
		{
			draw_line(mlx, x0, y0, x1, y1); // vers la droite / lignes horizontales
			tmp_x = x1;                    
			tmp_y = y1;
			x1 = x0 + 0;
			y1 = y0 + 10;
			if (j == map->col - 1 && y0 <= 10 * map->row )
				draw_line(mlx, tmp_x, tmp_y, x1 + 10, y1);
			if (i != map->row)
				draw_line(mlx, x0, y0, x1, y1); // vers le bas / lignes verticales 
			x1 = tmp_x + 10;
			y1 = tmp_y + 0;
			x0 = tmp_x;
			y0 = tmp_y;
		}
		x0 = 10;
		x1 = x0 + 10;
		y0 = tmp_y + 10;
		y1 = y0 + 0;
		i++;
	}
}




int ft_mlx_init(t_mlx *mlx, t_map *map)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (MLX_ERROR);
	mlx->win = mlx_new_window(mlx->ptr,  WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (!mlx->win)
		return (free(mlx->win), MLX_ERROR);
	mlx->img = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
	draw_map(mlx, map);
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
	ft_mlx_init(&mlx, &map);
	//if (ft_mlx_init(&mlx, &map) == MLX_ERROR)
	//	return (0);
	return (0);
}
