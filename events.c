/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 07:58:06 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/15 17:19:43 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

int handle_no_event(void *mlx)
{
	(void)*mlx;
	return (0);
}

// Si la touche symbole correspond bien a ESC, je ferme la fenetre.
int	handle_input(int keycode, t_mlx **mlx)
{
	//printf pour test
	if (keycode == ESC)
	{
		mlx_destroy_window((*mlx)->ptr, (*mlx)->win);
		mlx_destroy_image((*mlx)->ptr, (*mlx)->img);
		
		//mlx_loop_end(mlx->ptr);
		//free(mlx->ptr);
		exit(1); // comment shut le prog ? 
	}
	return (0);
}
