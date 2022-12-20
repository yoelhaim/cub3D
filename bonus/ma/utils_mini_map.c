/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:06:19 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/20 22:19:03 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	add_mini_map(t_mini_map *minimap, t_data *data, int x, int y)
{
	while (data->cub->maps[minimap->i][minimap->j] \
			&& minimap->j < minimap->right && minimap->l \
			< minimap->right - minimap->left + 2)
	{
		minimap->mini_map[minimap->k][minimap->l] = \
		data->cub->maps[minimap->i][minimap->j];
		if (minimap->i == y && minimap->j == x)
			minimap->mini_map[minimap->k][minimap->l] = 'E';
		minimap->j++;
		minimap->l++;
	}
}

void	get_mini_map(t_data *data, int x, int y, t_mini_map *minimap)
{
	int	size;

	while (data->cub->maps[minimap->i] && \
	minimap->i < minimap-> bottom && \
	minimap->k < minimap->bottom - minimap->top + 2)
	{
		size = minimap->right - minimap->left + 2;
		minimap->mini_map[minimap->k] = (char *)ft_calloc(size, sizeof(char));
		if (!minimap->mini_map[minimap->k])
			exit (0);
		minimap->j = minimap->left;
		minimap->l = 0;
		add_mini_map(minimap, data, x, y);
		minimap->i++;
		minimap->k++;
	}	
}

int	ft_get_val(int n)
{
	n -= 10;
	if (n < 0)
		n = 0;
	return (n);
}

int	ft_get_val_plus(int n, int p)
{
	n += 10;
	if (n > p)
		n = p;
	return (n);
}

char	**check_m_map(t_data *data, int x, int y)
{
	t_mini_map	*minimap;
	int			size;

	minimap = &data->minimap;
	minimap->top = ft_get_val(y);
	minimap->left = ft_get_val(x);
	minimap->right = ft_get_val_plus(x, data->cub->width_of_map);
	minimap->bottom = ft_get_val_plus(y, data->cub->height_of_map);
	size = minimap->bottom - minimap->top + 2;
	minimap->mini_map = calloc(size, sizeof(char *));
	if (!minimap->mini_map)
		exit (0);
	minimap->i = minimap->top;
	minimap->k = 0;
	get_mini_map(data, x, y, minimap);
	return (minimap->mini_map);
}
