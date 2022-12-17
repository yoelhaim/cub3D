/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:38:24 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/15 13:51:18 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_line_width(t_cub3d *cubmap)
{
	int	i;
	size_t	length;

	i = 0;
	length = 0;
	while (cubmap->maps[i])
	{
		if (cubmap->maps[i])
		{
			if (ft_strlen(cubmap->maps[i]) > length)
				length = ft_strlen(cubmap->maps[i]);
		}
		i++;
	}
	cubmap->width_of_map = length;
}

int	scq_map(t_cub3d *cubmap)
{
	int	i;
	int	j;

	i = 0;
	while (cubmap->maps[i][0] == '\n' && cubmap->maps[i][0])
		cubmap->maps[i++] = 0;
	i = 0;
	while (cubmap->maps[i])
	{
		j = 0;
		while (cubmap->maps[i][j])
		{
			if (cubmap->maps[i][j] == '\t')
				cubmap->maps[i][j] = ' ';
			j++;
		}
		i++;
	}
	get_line_width(cubmap);
	return (1);
}

int check_maps_2(t_cub3d *cubmap, int fd, int size)
{
	int		i;
	char	*str;

	int for_test = 0;
	i = 0;
	cubmap->maps = malloc(sizeof(char *) * size);
	while (i < size)
	{
		str = get_next_line(fd);
		if (!str)
			break;
		if (strlen(str)  >= 1 && str[0] != '\n')
		{
			cubmap->maps[i] = ft_strtrim(str, "\n");
			for_test = 1;
		}
		else
			i -= 1;
		i++;
	}
	cubmap->maps[i] = 0;
	close(fd);
	return (scq_map(cubmap));
}

void	get_map(int size, int fd, t_cub3d *cubmap)
{
	int		length;
	char	*str;
	int		last_size;

	length = 0;
	last_size = 0;
	cubmap->map = malloc(sizeof(char *) * size);
	if (!cubmap->map)
		return ;
	while (length < size)
	{
		if (length >= 6)
			break ;
		str = ft_strtrim(get_next_line(fd), " \t\n");
		if (ft_strlen(str) != 0)
			cubmap->map[length] = str;
		else
		{
			free(str);
			length -= 1;
		}
		length++;
		last_size++;
	}
	check_maps_2(cubmap, fd, size);
	cubmap->last_index = last_size;
	cubmap->map[length] = 0;
	close(fd);
}
