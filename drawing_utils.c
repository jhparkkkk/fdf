/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 16:30:33 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/22 17:21:33 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

char	**free_data(char **line_data)
{
	int	i;

	i = 0;
	while (line_data[i])
	{
		free(line_data[i]);
		i++;
	}
	free(line_data);
	return (NULL);
}

void	free_plan(int **line_data)
{
	int	i;

	i = 0;
	while (line_data[i])
	{
		free(line_data[i]);
		i++;
	}
	free(line_data);
}

float	f_abs(float nb)
{
	if (nb < 0)
		return (nb *= -1);
	return (nb);
}

void	find_sign(t_point *a, t_point *b, t_point *sign)
{
	if (a->x < b->x)
		sign->x = 1;
	else
		sign->x = -1;
	if (a->y < b->y)
		sign->y = 1;
	else
		sign->y = -1;
}

void	check_movement(t_mlx *mlx, t_point *start, t_point *end)
{
	start->y += mlx->gap_y;
	end->y += mlx->gap_y;
	start->x += mlx->gap_x;
	end->x += mlx->gap_x;
}
