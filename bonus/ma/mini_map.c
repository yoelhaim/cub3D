/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:03:08 by matef             #+#    #+#             */
/*   Updated: 2022/12/20 23:12:56 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static	double	ft_grid(double x)
{
	return ((GRID_SIZE * x));
}

static	t_rect	ft_rect(double j, double i, int color)
{
	return ((t_rect){ft_grid(j), ft_grid(i), ft_grid(1), ft_grid(1), color});
}

void	draw_map(t_data *data)
{
	int		i;
	int		j;
	char	**map;

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

void	ft_mini_map(t_data *data)
{
	t_mini_map_2	mini;

	mini = data->mini;
	mini.mini_map = check_m_map(data, (int)(data->p1.x / GRID_SIZE), \
	(int)(data->p1.y / GRID_SIZE));
	mini.w = ft_strlen(mini.mini_map[0]);
	mini.h = ft_len_ptr(mini.mini_map);
	mini.p1 = 0;
	mini.p2 = 0;
	mini.i = 15;
	while (mini.i < 110)
	{
		mini.j = 15;
		mini.p2 = 0;
		render_mini_map(data, &mini);
		mini.p1++;
		mini.i += 5;
	}
	free_texture(mini.mini_map);
}
