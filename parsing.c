/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/03/28 04:19:54 by jeepark          ###   ########.fr       */
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

void	point_init(t_point *point, int height)
{
	
	point->x = (point->x - point->y) * cos(0.523599);
	point->y = (point->x + point->y) * sin(0.523599) - height;
}	

void draw_line(t_mlx *mlx, t_point *a, t_point *b, int height)  
{
	printf("HEIGHT = %d\n", height);
	if (height)
	{
		point_init(a, height);
		point_init(b, height);
	}
	int dx =  fabs(b->x - a->x), sx = a->x < b->x ? 1 : -1;
	int dy = -fabs(b->y - a->y), sy = a->y <b->y ? 1 : -1; 
	int err = dx+dy, e2; /* error value e_xy */
	
	for(;;){  /* loop */
      put_pixel(mlx, a->x,a->y, 0xFF0000);
      if (a->x==b->x && a->y==b->y) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; a->x += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; a->y += sy; } /* e_xy+e_y < 0 */
   }
}

void	draw_map(t_mlx *mlx, t_map *map)
{
	int i = -1;
	int j = -1;
	t_point a;
	t_point b;
	a.x = 10;
	a.y = 10;
	b.x = 20;
	b.y = 10;
	int tmp_x = 0;
	int tmp_y = 0;

	printf("\ncolumns = %d\n", map->col);
	printf("\nrow = %d\n", map->row);
	//draw_line(mlx, x0, y0, x1, y1);
	while (++i < map->row)
	{
		draw_line(mlx, &a, &b, map->plan[i][j]);
		j = -1;
		while(++j < map->col)
		{
			draw_line(mlx, &a, &b, map->plan[i][j]); // vers la droite
			tmp_x = b.x;                    
			tmp_y = b.y;
			b.x = a.x + 0;
			b.y = a.y + 10;
			draw_line(mlx, &a, &b, map->plan[i][j]); // vers le bas
			b.x = tmp_x + 10;
			b.y = tmp_y + 0;
			a.x = tmp_x;
			a.y = tmp_y;
			//if (j == map->col)
			//	draw_line(map, mlx, x0, y0, x1 - 10, y1 + 10, i, j);
		}
		a.x = 10;
		b.x = a.x + 10;
		a.y = tmp_y + 10;
		b.y = a.y + 0;
		//if (i == map->row)
		//	draw_line(map, mlx, x0, y0, x0 * map->row * 2, y1, i, j);
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
	//int i = 0;
	//int j = 0;
	t_map	map;
	t_mlx	mlx;
	if (ac < 2)
		return (0);
	read_map(av, &map);
	/*while(i < map.row)
	{
		j = 0;
		printf("\n");
		while(j < map.col)
		{
			printf("%d", map.plan[i][j]);
			j++;
		}
		i++;
	}*/
	ft_mlx_init(&mlx, &map);
	//if (ft_mlx_init(&mlx, &map) == MLX_ERROR)
	//	return (0);
	return (0);
}
