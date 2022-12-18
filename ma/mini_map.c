/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:03:08 by matef             #+#    #+#             */
/*   Updated: 2022/12/18 22:03:26 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static double ft_grid(double x)
{
	return ((GRID_SIZE * x));
}

static t_rect ft_rect(double j, double i, int color)
{
	return ((t_rect){ft_grid(j), ft_grid(i), ft_grid(1), ft_grid(1), color});
}

void draw_map(t_data *data)
{
	int i;
	int j;
    char **map;
    
	i = 0;
	map = data->cub->maps;
    while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				render_rect(&data->img, ft_rect(j, i, WALL));
			else if (map[i][j] == '0')
				render_rect(&data->img, ft_rect(j, i, SPACE));
			j++;
		}
		i++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int ft_get_val(int n)
{
	n -= 10;
	if (n < 0)
		n = 0;
	return n;
}

int ft_get_val_plus(int n, int p)
{
	n += 10;
	if (n > p)
		n = p;
	return n;
}

char	**check_m_map(t_data *data, int x, int y)
{
	printf("player position %d %d\n", x, y);

	int top = ft_get_val(y);
	int left = ft_get_val(x);

	int right = ft_get_val_plus(x, data->cub->width_of_map);
	int bottom = ft_get_val_plus(y, data->cub->height_of_map);

	char **mini_map;

	int lw = bottom - top + 2, lh = right - left + 2;
	mini_map = (char **)calloc(lw , sizeof(char *));
	if (!mini_map)
		exit (0);

	int i = top, j;
	int k = 0, l;
	

	while (data->cub->maps[i] && i <  bottom && k < lw)
	{
		mini_map[k] = (char *)calloc(lh, sizeof(char));
		if (!mini_map[k])
			exit (0);

		j = left;
		l = 0;
		while (data->cub->maps[i][j] && j < right && l < lh)
		{
			mini_map[k][l] =  data->cub->maps[i][j];

			if (i == y && j == x)
				mini_map[k][l] = 'E';

			j++;
			l++;
		}
		i++;
		k++;
	}
	return (mini_map);
}


void ft_mini_map(t_data *data)
{
	char **mini_map = check_m_map(data, (int)(data->p1.x / GRID_SIZE), (int)(data->p1.y / GRID_SIZE));
	
	int i = 0;
	while (mini_map[i])
	{
		printf("%s\n", mini_map[i]);
		i++;
	}
	

	
	int h,w;

	w = ft_strlen(mini_map[0]) ;
	h = ft_len_ptr(mini_map);
	printf("sss %d %d\n", w, h);
	int p1 = 0,p2 = 0;
	int j;
	 i =15;
	 while (i < 200)
	 {
		 j = 15;
		 p2 = 0;
		 while (j < 200 )
		 {
			// render_rect(&data->img, (t_rect){i,j, 10, 10, YELLOW});
			if ( p1 < h && p2 <= w )
			{
				if (mini_map[p1][p2] == '1')
					render_rect(&data->img, (t_rect){j,i, 10, 10, RED});
				if (mini_map[p1][p2] == '0')
					render_rect(&data->img, (t_rect){j,i, 10, 10, 0xff0});
				if (mini_map[p1][p2] == 'X')
					render_rect(&data->img, (t_rect){j,i, 10, 10, 0xff0});
				if (mini_map[p1][p2] == 'E')
					render_rect(&data->img, (t_rect){j,i, 10, 10, YELLOW});
				
			}
			p2++;
			j+= 10;
			
			
		 }
		 p1++;
		i+= 10;
	 }
	 free_texture(mini_map);
}