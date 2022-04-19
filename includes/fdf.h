/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:46:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/19 17:10:57 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MLX_ERROR 1 
# define ESC 53
# define GO_LEFT 123
# define GO_RIGHT 124
# define GO_UP 126
# define GO_DOWN 125
# define HIGHER 13
# define LOWER 1
# define PLUS 24
# define MINUS 27
# define ROTATE_RIGHT 2
# define ROTATE_LEFT 0

//# include <X11/X.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"


typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		gap_x;
	int		gap_y;
	
}			t_mlx;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color; 
}			t_point;

typedef struct s_map
{
	int 	row;
	int 	col;
	int		fil;
	int		tile_x;
	int		tile_y;
	int		gap_z;
	float	angle_x;
	int		**plan;
	t_point	**matrix; 
	t_mlx	*mlx;
	int		zoom;
}			t_map;

/*-----------*INIT*------------*/

void	read_map(char **av, t_map *map);
int		ft_mlx_init(t_mlx *mlx);

/*---------*DESTROY*-----------*/
void	destroy_mlx(t_mlx *mlx);

/*---------*EVENTS*-----------*/
int		handle_no_event(void *mlx);
int		press_key(int keycode, t_map *map);
void	new_image(t_mlx *mlx, t_map *map);
/*---------*MATRIX*-----------*/
void	matrix_init(t_map *map);
void	matrix_iso(t_map *map);

/*---------*DRAWING*-----------*/
void	put_pix(t_mlx *mlx, int x, int y, int color);

void	draw_line(t_mlx *mlx, float ax, float ay, float bx, float by);  
void	draw_map(t_map *map, t_mlx *mlx);

void	try(t_mlx *mlx, t_map *map, t_point *a, t_point *b);
float	f_abs(float nb);
void	find_sign(float ax, float ay, float bx, float by, t_point *sign);
void	check_movement(t_mlx *mlx, float *ax, float *ay, float *bx, float *by);

#endif