/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/03/19 19:12:47 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

typedef struct s_data
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_len;
    int     endian;
}			t_data;              

/*void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}*/

/*int parsing(int fd)
{
	if (read(fd, buffer, 0) == -1)
		return (NULL);
}*/

// j'initialise la minilibx --> il s'agit d'un pointeur sur une structure
//contenant tous les outils graphiques dont j'ai besoin.


void	ft_mlx_destroy(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	//mlx_destroy_image(mlx->ptr);
	free(mlx->ptr);
}

int handle_no_event(void *mlx)
{
	(void)*mlx;
	return (0);
}

// Si la touche symbole correspond bien a ESC, je ferme la fenetre.
int	handle_input(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
		mlx_destroy_window(mlx->ptr, mlx->win);
	return (0);
}

int ft_mlx_init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (MLX_ERROR);
	mlx->win = mlx_new_window(mlx->ptr,  WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (!mlx->win)
		return (free(mlx->win), MLX_ERROR);
	mlx_loop_hook(mlx->ptr, &handle_no_event, &mlx);
	mlx_key_hook(mlx->win, &handle_input, &mlx);
	mlx_loop(mlx->ptr);
	return (0);
}

void	tab_init(t_map *map)
{
	map->plan = malloc(sizeof(int *) * map->row + 1);
	if (!map->plan)
		free(map->plan);
}

void	line_counter(char **av, t_map *map)
{
	char buf[1];
	int ret = 1;
	int fd;
	
	fd = open(av[1], O_RDONLY);
	map->row = 0;
    while (ret != 0) 
	{
		ret = read(fd, buf, 1);
        if (buf[0] == '\n') 
        	map->row++;
    }
	close(fd);
}

void data_count(char const *s, char c, t_map *map)
{
	int	i;
	
	i = 0;
	if (!s)
		return ;
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

// J'initialise mon tableau de hauteur 

void	save_map(char *line, t_map *map)
{
	char		**line_data;
	size_t		i = 0;
	size_t		j = 0;
	int			data = 0;
	static int	line_no = 0;
	
	data_count(line, ' ', map);
	line_data = ft_split(line, ' ');
	/*while(i < (size_t)map->row)
	{
		j= 0;
		printf("NO. %zu\n", i);
		while(j < limit)
		{
			printf("LINE_DATA[%zu][%zu] = %c\n", i, j, line_data[i][j]);
			j++;
		}
		i++;
	}*/
	if (!map->plan || !line_data)
		return ;
	while (i < (size_t)map->col)
	{
		j = 0;
		map->plan[line_no] = malloc(sizeof(int) * (map->col + 1));
		map->plan[line_no][data] = ft_atoi(&line_data[i][j]);
		j++;
		data++; 
		i++;
	}
	if (line_no == map->row + 1)
		map->plan[line_no] = 0;
	map->plan[line_no][data] = '\0';
}


// Je compte le nb de ligne de ma map 

void	read_map(char **av, t_map *map)
{
	int fd = 0;
	int i = 0;
	int j = 0;
	char *line = NULL;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return ;
	line_counter(av, map);
	tab_init(map);
	while (i < map->row)
	{
		line = get_next_line(fd);
		save_map(line, map);
		free(line);
		i++;
	}
	i = 0;
	j = 0;
	while (i < map->row)
	{
		j = 0;
		while(j < map->col)
		{
			printf("MAP->PLAN[%d][%d] = %d", i ,j, map->plan[i][j]);
			j++;
		}
		i++;
	}
	
}

int	main(int ac, char **av)
{
	t_map	map;
	if (ac < 2)
		return (0);
	read_map(av, &map);
	
	/*if (ft_mlx_init(&mlx) == MLX_ERROR)
		return (0);
	

    img.img = mlx_new_image(mlx.ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	
	while(i < 100)
	{
		j = 0;
		while(j < 1)
		{
			mlx_pixel_put(mlx.ptr, mlx.win, j, i, 0xFF00FF00);
			j++;
		}
		i++;
	}*/
	return (0);
}
