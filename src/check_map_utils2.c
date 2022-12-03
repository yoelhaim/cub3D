/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:38:24 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/02 14:57:24 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	scq_map(t_cub3d *cubmap)
{
	int	i;
	int	j;

	i = 0;
	while (cubmap->maps[i])
	{
		j = 0;
		if (ft_strlen(cubmap->maps[i]) == 1)
			cubmap->maps[i] = " ";
		while (cubmap->maps[i][j])
		{
			if (cubmap->maps[i][j] == '\t')
				cubmap->maps[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (1);
}

int check_maps_2(t_cub3d *cubmap, int fd, int size)
{
	int		i;
	char	*str;

	i = 0;
	cubmap->maps = malloc(sizeof(char *) * size);
	while (i < size)
	{
		str = get_next_line(fd);
		if (!str || str[0] == '\0')\
			break;
			
		// printf(	"%s\n", str);
		if (strlen(str)  >= 1 && str[0] != '\n')
			cubmap->maps[i] = str;
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
	while (length < size)
	{
		str = ft_strtrim(get_next_line(fd), " \t\n");
		if (length >= 6)
			break ;
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
