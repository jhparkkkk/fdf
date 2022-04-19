/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 16:30:33 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/18 14:01:53 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

float f_abs(float nb)
{
	if (nb < 0)
		return (nb *= -1);
	return (nb);
}

void	find_sign(float ax, float ay, float bx, float by, t_point *sign)
{
	if (ax < bx)
		sign->x = 1;
	else
		sign->x = -1;

	if (ay < by)
		sign->y = 1;
	else
		sign->y = -1;
}

void	check_movement(t_mlx *mlx, float *ax, float *ay, float *bx, float *by)
{
	*ay += mlx->gap_y;
	*by += mlx->gap_y;
	*ax += mlx->gap_x;
	*bx += mlx->gap_x;
}