/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 10:39:36 by jeepark           #+#    #+#             */
/*   Updated: 2022/05/02 16:41:42 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_init(t_map *map)
{
	map->angle_x = M_PI / 6;
	map->gap_z = 1.0;
	map->zoom = 1.0;
	map->row = 0;
	map->col = 0;
	map->fil = 0;
}

void	check_extension(char **av)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (av[1][i])
	{
		if (av[1][i] == '.' )
		{
			flag = 1;
			if (ft_strcmp(&av[1][i], ".fdf") != 0)
			{
				write(STDERR_FILENO, "wrong file\n", 11);
				exit(1);
			}
		}
		i++;
	}
	if (flag == 0)
	{
		write(STDERR_FILENO, "wrong file\n", 11);
		exit(1);
	}
}
