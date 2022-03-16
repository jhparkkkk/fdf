/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:51:59 by jeepark           #+#    #+#             */
/*   Updated: 2022/03/16 18:05:57 by jeepark          ###   ########.fr       */
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
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
}

int handle_no_event(void *mlx)
{
	(void)*mlx;
	return (0);
}

// Si la touche symbole correspond bien a ESC, je ferme la fenetre.
int	handle_input(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
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

static char	**tab_init(t_map *map)
{
	char	**tab;
	printf("MAP->ROW = %i\n", map->row);
	tab = malloc(sizeof(char *) * (map->row + 1));
	if (!tab)
		return (free(tab), NULL);
	return (tab);
}

/*size_t	data_count(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}*/

int	data_count(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c && s[i])
			i++;
	}
	return (word);
}

// J'initialise mon tableau de hauteur 

void	save_map(char *line, t_map *map)
{
	char		**plan;
	char		**line_data;
	size_t		i = 0;
	size_t		j = 0;
	size_t		data = 0;
	static int	line_no = 1;
	size_t		limit;
	
	plan = tab_init(map);
	line_data = ft_split(line, ' ');
	if (!plan || !line_data)
		return ;
	limit = data_count(line, ' ');
	printf("LIMIT = %zu\n", limit);
	while (i < limit)
	{
		j = 0;
		plan[line_no] = malloc(sizeof(char) * 2 );
		while (line_data[i][j])
		{
			plan[line_no][data] = line_data[i][j];
			j++; 
			data++;
		}
		i++;
	}
	if (line_no == 14)
		plan[line_no] = 0;
	plan[line_no][data] = 0;
	i = 0;
	printf("plan[0][%zu] = %s\n", i, plan[i]);
}

// Je compte le nb de ligne de ma map 

void	read_map(char **av, t_map *map)
{
	int fd = 0;
	char *line = NULL;
	
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return ;
	map->row = -1;
	while (line != NULL || map->row == -1)
	{
		line = get_next_line(fd);
		save_map(line, map);
		free(line);
		map->row++;
	}
	printf("how many lines = %d\n", map->row);
	printf("ICI -----> %d", map->row);
}

int	main(int ac, char **av)
{
	//int		fd;
	//void	*mlx_ptr;
	//void	*win_ptr;
	//t_mlx	mlx;
	//t_data	img;
	//int 	i = 0;
	//int		j;
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
