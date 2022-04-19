/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 00:13:04 by jeepark           #+#    #+#             */
/*   Updated: 2022/04/19 13:31:07 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int  line_counter(char **av, t_map *map)
{
	char buf[1];
	int ret = 1;
	int fd;
	
	fd = open(av[1], O_RDONLY);
	map->row = 0;
    while (ret != 0) 
	{
        if (buf[0] == '\n') 
        	map->row++;
		ret = read(fd, buf, 1);
    }
	close(fd);
	return(map->row);
}

static void tab_init(char **av, t_map *map)
{
	map->plan = (int **)malloc(sizeof(int *) * (line_counter(av, map) + 2));
	if (!map->plan)
		free(map->plan);	
}


void column_counter(char const *s, char c, t_map *map)
{
	int	i;
	
	i = 0;
	if (!s)
		return ;
	map->col = -1;
	while (s[i])
	{
		if (s[i] != c)
		{
			map->col++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c && s[i])
			i++;
	}
}

static char	**free_data(char **line_data)
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

static void free_plan(int **line_data)
{
	int	i;

	i = 0;
	while (line_data[i])
	{
		free(line_data[i]);
		i++;
	}
	free(line_data);
	//return (NULL);
}

// J'initialise mon tableau de hauteur 

void	save_map(char *line, t_map *map)
{
	char		**line_data;
	size_t		i;
	size_t		j;

    i = 0;
    j = 0;
	line_data = ft_split(line, ' ');
	if (!map->plan || !line_data)
		return ;
	map->plan[map->fil] = malloc(sizeof(int) * (map->col + 2));
    if (!map->plan[map->fil])
        free_plan(map->plan);
	while (line_data[i])
	{
		map->plan[map->fil][j] = ft_atoi(line_data[i]);
		j++;
		i++;
	}
	free_data(line_data);
	if (map->fil == map->row - 1)
		map->plan[map->fil + 1] = 0;
	map->plan[map->fil][j] = '\0';
	map->fil++;
}


// Je compte le nb de ligne de ma map 

void	read_map(char **av, t_map *map)
{
	int fd = 0;
	int i = 0;
	char *line = NULL;
    
	map->gap_z = 0;
	map->zoom = 0;
    line_counter(av, map);
	tab_init(av, map);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return ;
	map->fil = 0;
	while (i <= map->row)
	{
		line = get_next_line(fd);
		if (i == 0)
			column_counter(line, ' ', map);
		save_map(line, map);
		free(line);
		i++;
	}
}
