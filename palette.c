/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:31:19 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/11 10:58:48 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

double percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

int put_color(t_point *curr, t_point *start, t_point *end, t_point *delta)
{
    int red;
    int green;
    int blue;
    double percentage;

    if (curr->color == end->color)
        return(curr->color);
    if (delta->y > delta->x)
        percentage = percent(start->x, end->x, curr->x);
    else
        percentage = percent(start->y, end->y, curr->y);
    red = get_light((start->color >> 16) & 0xFF, (end->color >> 16) & 0xFF, percentage);
    green = get_light((start->color >> 8) & 0xFF, (end->color >> 8) & 0xFF, percentage);
    blue = get_light(start->color & 0xFF, end->color & 0xFF, percentage);
    return(red >> 16 | green >> 8 | blue);
}