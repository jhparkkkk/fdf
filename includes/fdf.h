/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:46:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/23 20:14:37 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MLX_ERROR 1
# define FD_ERROR -1
# define ESC 65307
# define GO_LEFT 65361
# define GO_RIGHT 65363
# define GO_UP 65362
# define GO_DOWN 65364
# define HIGHER 119
# define LOWER 115
# define PLUS 61
# define MINUS 45
# define ROTATE_RIGHT 100
# define ROTATE_LEFT 97

# include <X11/X.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		end;
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

typedef struct s_bres
{
	t_point	distance; 
	t_point sign; 
	t_point start; 
	t_point end;
	int		error_0;
	int		error_1;
}			t_bres;

/*-----------*INIT*------------*/

int		read_map(char **av, t_map *map);
int		ft_mlx_init(t_mlx *mlx);

/*---------*DESTROY*-----------*/
void	destroy_mlx(t_mlx *mlx, t_map *map);

/*---------*EVENTS*-----------*/
int		handle_no_event(void *mlx);
int		press_key(int keycode, t_map *map);
void	new_image(t_mlx *mlx, t_map *map);
char	**free_data(char **line_data);
void	free_plan(int **line_data);

/*---------*SETTINGS*-----------*/
void	set_move(t_mlx *mlx, t_map *map, int keycode);
void	set_altitude(t_mlx *mlx, t_map *map, int keycode);
void	set_zoom(t_mlx *mlx, t_map *map, int keycode);
void	set_angle(t_mlx *mlx, t_map *map, int keycode);
/*---------*MATRIX*-----------*/
void	matrix_init(t_map *map);
void	matrix_iso(t_map *map);
void	matrix_destroy(t_map *map);

/*---------*DRAWING*-----------*/
void	put_pix(t_mlx *mlx, int x, int y, int color);

void	draw_line(t_mlx *mlx, t_point *a, t_point *b);  
void	draw_map(t_map *map, t_mlx *mlx);

float	f_abs(float nb);
void	find_sign(t_point *a, t_point *b, t_point *sign);
void	check_movement(t_mlx *mlx, t_point *a, t_point *b);

#endif