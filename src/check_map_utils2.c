/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:38:24 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/22 15:31:40 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_line_width(t_cub3d *cubmap)
{
	int		i;
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
	if (!cubmap->maps[i])
		return (ft_putendl_fd("Error\nMap not Found ❌", 2), 0);
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

void	add_to_map(int *first_line, char **maps, char *str, int *i)
{
	if (ft_strlen(str) >= 1)
	{
		*first_line = 1;
		maps[*i] = ft_strtrim(str, "\n");
	}
	else
		*i -= 1;
}

int	check_maps_2(t_cub3d *cubmap, int fd, int size, int first_line)
{
	int		i;
	char	*str;

	i = 0;
	cubmap->maps = ft_calloc(size + 1, sizeof(char *));
	while (i < size)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (str[0] == '\n' && !first_line)
		{
			free(str);
			continue ;
		}
		add_to_map(&first_line, cubmap->maps, str, &i);
		free(str);
		i++;
	}
	close(fd);
	return (scq_map(cubmap));
}

void	get_map(int size, int fd, t_cub3d *cubmap)
{
	int	last_size;
	int	first_line;

	first_line = 0;
	last_size = 0;
	cubmap->map = ft_calloc(size + 2, sizeof(char *));
	if (!cubmap->map)
		return ;
	last_size = add_textur_color(cubmap->map, fd, size, last_size);
	if (!check_maps_2(cubmap, fd, size, first_line))
		exit(1);
	cubmap->last_index = last_size;
	close(fd);
}
