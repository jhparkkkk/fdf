/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/03 05:07:33 by jeepark          ###   ########.fr       */
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



void draw_line(t_mlx *mlx, t_point *a, t_point *b)  
{
	float x = a->x;
	float y = a->y;
	int dx =  fabs(b->x - a->x), sx = a->x < b->x ? 1 : -1;
	int dy = -fabs(b->y - a->y), sy = a->y < b->y ? 1 : -1; 
	int err = dx+dy, e2; /* error value e_xy */
	
	while (1)
	{
		put_pixel(mlx, x, y, 0xFF0000);
		if (x == b->x && y == b->y) 
			break;
		e2 = 2 * err;
      	if (e2 >= dy)
	  	{
			  err += dy;
			  x += sx; 
		} /* e_xy+e_x > 0 */
    	if (e2 <= dx) 
	  	{
			  err += dx;
			  y += sy;
		} /* e_xy+e_y < 0 */
   }
}

void	put_height(t_map *map, int x, int y)
{
	x = (x - y) * cos(0.523599);
	y = (x + y) * sin(0.523599) - map->plan[y][x];
}

void final_touch(t_mlx *mlx, t_point *tmp, t_point *b)
{
	b->x += 10;
	draw_line(mlx, tmp, b);
	b->x -= 10;
}


void	next_row(t_map *map, t_point *a, t_point *b, int i)
{
	a->x = ((WINDOW_WIDTH / 3) - (i*(map->tile_width / 2)));
	a->y = ((WINDOW_HEIGHT / 3) + (i*(map->tile_height / 2))); 
	b->x = a->x + map->tile_width / 2;
	b->y = a->y + map->tile_height / 2;
}

void	coord_init(t_map *map, t_point *a, t_point *b)
{	
	a->x = WINDOW_WIDTH / 3;
	a->y = WINDOW_HEIGHT / 3;
	b->x = a->x + map->tile_width / 2;
	b->y = a->y + map->tile_height / 2;
}


void go_down(t_map *map, t_point *tmp, t_point *a, t_point *b)
{
	tmp->x = b->x;                    
	tmp->y = b->y;
	b->x = a->x - map->tile_width / 2;
	b->y = a->y + map->tile_height / 2; 
}

void	go_right(t_map *map, t_point *tmp, t_point *a, t_point *b)
{
	b->x = a->x + map->tile_width / 2;
	b->y = a->y + map->tile_height / 2;
	a->x = tmp->x;
	a->y = tmp->y;
}

void	draw_map(t_mlx *mlx, t_map *map, t_point *a, t_point *b)
{
	int i;
	int j;
	t_point tmp;
	
	coord_init(map, a, b);
	i = -1;
	while (++i <= map->row)
	{
		j = 0;
		while(j++ < map->col)
		{
			draw_line(mlx, a, b);
			go_down(map, &tmp, a, b);
			//if (j == map->col && i < map->row)
			//	final_touch(mlx, &tmp, b);
			if (i != map->row)
				draw_line(mlx, a, b);
			go_right(map, &tmp, a, b);
		}
		next_row(map, a, b, i);	
	}
}



int ft_mlx_init(t_mlx *mlx, t_map *map, t_point *a, t_point *b)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (MLX_ERROR);
	mlx->win = mlx_new_window(mlx->ptr,  WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (!mlx->win)
		return (free(mlx->win), MLX_ERROR);
	mlx->img = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
	
	//try(mlx, map, a, b);
	draw_map(mlx, map, a, b);
	
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
	t_point	a;
	t_point b;
	if (ac < 2)
		return (0);
	read_map(av, &map);
	printf("COLUMNS = %d\n", map.col);
	while(i <= map.row)
	{
		j = 0;
		printf("\n");
		while(j <= map.col)
		{
			printf("%d ", map.plan[i][j]);
			j++;
		}
		i++;
	}
	map.tile_width = 40;
	map.tile_height = 20;
	ft_mlx_init(&mlx, &map, &a, &b);
	//if (ft_mlx_init(&mlx, &map) == MLX_ERROR)
	//	return (0);
	return (0);
}