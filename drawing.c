/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/08 11:30:32 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

void	put_pixel(t_mlx *mlx, float x, float y, int color)
{
	char	*pix;
	
	if (x < 0 || y < 0 || x > WINDOW_WIDTH - 1 || y > WINDOW_HEIGHT)
		return ; 
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
		if ((int)x == (int)b->x && (int)y == (int)b->y) 
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


void final_touch(t_map *map, t_mlx *mlx, t_point *tmp, t_point *a, t_point *b)
{
	b->x = tmp->x - map->tile_width / 2;
	b->y = tmp->y + map->tile_height / 2;
	draw_line(mlx, tmp, b);
	b->x = a->x - map->tile_width / 2;
	b->y = a->y + map->tile_height / 2; 
}


void	next_row(t_map *map, t_point *a, t_point *b, int i)
{
	
	a->x = ((WINDOW_WIDTH / 3) - (i *(map->tile_width / 2)));
	a->y = ((WINDOW_HEIGHT / 3) + (i *(map->tile_height / 2))); 
	b->x = a->x + map->tile_width / 2;
	b->y = a->y + map->tile_height / 2;
}





void	go_right(t_map *map, t_point *tmp, t_point *a, t_point *b)
{
	a->x = tmp->x;
	a->y = tmp->y;
	b->x = a->x + map->tile_width;
	b->y = a->y + map->tile_height;
	
}

void go_down(t_map *map, t_point *tmp, t_point *a, t_point *b)
{
	tmp->x = b->x;                    
	tmp->y = b->y;
	b->x = a->x - map->tile_width;
	b->y = a->y + map->tile_height; 
}
void	coord_init(t_map *map, t_point *a, t_point *b, t_point *tmp)
{	
	//(void)map;
	tmp->x = 0;
	tmp->y = 0;
	a->x = WINDOW_WIDTH / 3;
	a->y = WINDOW_HEIGHT / 3;
	b->x = a->x + map->tile_width;
	b->y = a->y + map->tile_height;
	/*a->x = 0;
	a->y = 0;
	b->x = 0;
	b->y = 0;*/
}

static void iso(float *x, float *y, int z)
{
    float previous_x;
    float previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	try(t_mlx *mlx, t_map *map, t_point *a, t_point *b)
{
	t_point tmp;
	
	coord_init(map, a, b, &tmp);

}

/*void	draw_map(t_mlx *mlx, t_map *map, t_point *a, t_point *b)
{
	int i;
	int j;
	t_point tmp;
	
	coord_init(map, a, b);
	iso(a, map->plan[0][0]);
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while(j < map->col)
		{
			printf("\nI = %d | J = %d\n", i, j);
			draw_line(mlx, a, b);
			go_down(map, &tmp, a, b);
			if (j == map->col - 1 && i < map->row - 1)
				final_touch(map, mlx, &tmp, a, b);
			if (i != map->row - 1)
				draw_line(mlx, a, b);
			go_right(map, &tmp, a, b);
			j++;
		}
		i++;
		next_row(map, a, b, i);	
	}
}*/



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
	printf("COLUMNS = %d | ROWS = %d\n", map.col, map.row);
	while(i <= map.row)
	{
		j = 0;
		printf("\n");
		while(map.plan[i] && j < map.col)
		{
			printf("%d ", map.plan[i][j]);
			j++;
		}
		i++;
	}
	map.tile_width = 5;
	map.tile_height = 5;
	ft_mlx_init(&mlx, &map, &a, &b);
	//if (ft_mlx_init(&mlx, &map, &a, &b) == MLX_ERROR)
	//	return (0);
	return (0);
}