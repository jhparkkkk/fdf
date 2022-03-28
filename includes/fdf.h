/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:46:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/03/28 04:06:44 by jeepark          ###   ########.fr       */
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

typedef struct s_map
{
	int 	row;
	int 	col;
	int		fil;
	int		**plan;
}			t_map;

typedef struct s_point
{
	float	x;
	float	y;
}		t_point;

/*-----------*INIT*------------*/

int		ft_mlx_init(t_mlx *mlx, t_map *map);
void	read_map(char **av, t_map *map);


/*---------*DESTROY*-----------*/
void	ft_mlx_destroy(t_mlx *mlx);


#endif