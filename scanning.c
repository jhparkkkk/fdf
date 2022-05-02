/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 00:13:04 by jeepark           #+#    #+#             */
/*   Updated: 2022/05/02 09:29:44 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	line_counter(char **av, t_map *map)
{
	char	buf[1];
	int		ret;
	int		fd;

	buf[0] = 0;
	ret = 1 ;
	fd = open(av[1], O_RDONLY);
	if (read(fd, buf, 0) == FD_ERROR)
		return (FD_ERROR);
	map->row = 0;
	while (ret != 0)
	{
		if (buf[0] == '\n')
			map->row++;
		ret = read(fd, buf, 1);
	}
	close(fd);
	return (map->row);
}

static void	tab_init(char **av, t_map *map)
{
	int	line;

	line = line_counter(av, map);
	if (line == FD_ERROR)
		exit (1);
	map->plan = (int **)malloc(sizeof(int *) * (line + 2));
	if (!map->plan)
	{
		free(map->plan);
		exit (1);
	}
}

static void	column_counter(char const *s, char space, t_map *map)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	map->col = -1;
	while (s[i])
	{
		if (s[i] != space)
		{
			map->col++;
			while (s[i] != space && s[i])
				i++;
		}
		while (s[i] == space && s[i])
			i++;
	}
}

void	save_map(char *line, t_map *map)
{
	char	**line_data;
	size_t	i;
	size_t	j;

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
	 if ((int)j - 1 != map->col)                   // error map
	 	write(2, "error\n", 6);
	free_data(line_data);
	if (map->fil == map->row - 1)
		map->plan[map->fil + 1] = 0;
	map->plan[map->fil][j] = '\0';
	map->fil++;
}

void check_line(t_map *map, char *line)
{
	int i;
	int line_len = ft_strlen(line);
	i = 0;
	(void)map;
	printf("%d\n", line_len);
	while(i < line_len)
	{
		//printf("yes\n");
		if (line[i] == '-')
		{
			if (ft_isdigit(line[i + 1] == 0))
				write(2, "error sign minus\n", 6);
		}
		if (ft_isdigit(line[i]) == 0 && line[i] != ' ' && line[i] != '\n' && line[i] != '-')
		{
			printf("oo%coo\n", line[i]);
			write(2, "error\n", 6);
			exit(1);
		}
		i++;
	}
}

int	read_map(char **av, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	fd = 0;
	i = 0;
	line = NULL;
	tab_init(av, map);
	fd = open(av[1], O_RDONLY);
	while (i <= map->row)
	{
		line = get_next_line(fd);
		if (i == 0)
			column_counter(line, ' ', map);
		check_line(map, line);
		save_map(line, map);
		free(line);
		i++;
	}
	return (0);
}
