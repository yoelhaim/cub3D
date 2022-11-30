/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:38:24 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/11/30 18:51:51 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_map(int size, int fd, t_cub3d *cubmap)
{
	int		length;
	char	*str;

	length = 0;
	cubmap->map = malloc(sizeof(char *) * size);
	while (length < size)
	{
		str = ft_strtrim(get_next_line(fd), " \t\n");
		if (strstr(str, "111"))/// khas ytbdal had chi
			break ;
		if (ft_strlen(str) != 0)
			cubmap->map[length] = str;
		else
		{
			free(str);
			length -= 1;
		}
		length++;
	}
	cubmap->map[length] = 0;
	close(fd);
}

int	scq_map(t_cub3d *cubmap)
{
	int	i;
	int	j;

	i = 0;
	while (cubmap->maps[i])
	{
		j = 0;
		if (ft_strlen(cubmap->maps[i]) == 1)
			cubmap->maps[i] = "-";
		while (cubmap->maps[i][j])
		{
			if (cubmap->maps[i][j] == ' ' || cubmap->maps[i][j] == '\t')
				cubmap->maps[i][j] = '-';
			j++;
		}
		i++;
	}
	return (1);
}

void	checksmapsandinsert(t_cub3d *cubmap, int size, char *str, int fd)
{
	int	i;

	i = 1;
	while (i < size)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		cubmap->maps[i++] = ft_strdup(str);
	}
	cubmap->maps[i] = 0;
	close(fd);
}

int	check_maps(t_cub3d *cubmap, char *namefile)
{
	int		fd;
	int		i;
	int		len;
	char	*str;

	fd = open(namefile, O_RDONLY);
	i = 0;
	len = -1;
	while (get_next_line(fd))
		i++;
	cubmap->maps = malloc(sizeof(char *) * i);
	if (!cubmap->maps)
		return (0);
	close(fd);
	fd = open(namefile, O_RDONLY);
	while (++len < i)
	{
		str = get_next_line(fd);
		if (strstr(str, "111"))
		{
			cubmap->maps[0] = ft_strdup(str);
			break ;
		}
	}
	checksmapsandinsert(cubmap, i, str, fd);
	return (scq_map(cubmap));
}
