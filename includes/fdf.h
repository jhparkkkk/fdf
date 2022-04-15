/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:46:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/15 17:18:14 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MLX_ERROR 1 
# define ESC 53

//# include <X11/X.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

/*typedef struct s_coord
{
	int		x;
	int		y;
}			t_coord;*/

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	
}			t_mlx;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int	color; 
}			t_point;

typedef struct s_map
{
	int 	row;
	int 	col;
	int		fil;
	int		tile_width;
	int		tile_height;
	int		**plan;
	t_point	**matrix; 
}			t_map;
/*-----------*INIT*------------*/

int		ft_mlx_init(t_mlx *mlx, t_map *map);
void	read_map(char **av, t_map *map);


/*---------*DESTROY*-----------*/
void	ft_mlx_destroy(t_mlx *mlx);

/*---------*EVENTS*-----------*/
int		handle_no_event(void *mlx);
int		handle_input(int keycode, t_mlx **mlx);

/*---------*MATRIX*-----------*/
void	matrix_init(t_map *map);
void	matrix_iso(t_map *map);

/*---------*DRAWING*-----------*/
void	put_pixel(t_mlx *mlx, int x, int y, int color);

void	draw_line(t_mlx *mlx, float ax, float ay, float bx, float by);  
void	draw_map(t_map *map, t_mlx *mlx);

void	try(t_mlx *mlx, t_map *map, t_point *a, t_point *b);

#endif