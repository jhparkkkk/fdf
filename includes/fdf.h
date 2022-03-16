/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:46:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/03/16 16:00:46 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MLX_ERROR 1 

# include <X11/keysym.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}			t_mlx;

typedef struct s_coord
{
	char	x;
	char	y;
}			t_coord;

typedef struct s_map
{
	int row;
	int col;
}		t_map;

/*-----------*INIT*------------*/

int ft_mlx_init(t_mlx *mlx);



/*---------*DESTROY*-----------*/
void	ft_mlx_destroy(t_mlx *mlx);


#endif