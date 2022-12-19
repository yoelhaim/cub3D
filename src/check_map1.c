/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/12/18 23:52:07 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_texture(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	check_doube_texture(char **map)
{
	int		i;
	char	**split;
	int		len;

	i = -1;
	len = 0;
	while (map[++i])
	{
		split = ft_split(map[i], ' ');
		if (ft_strstr(*split, "SO"))
			len++;
		if (ft_strstr(*split, "NO"))
			len++;
		if (ft_strstr(*split, "EA"))
			len++;
		if (ft_strstr(*split, "WE"))
			len++;
		if (ft_strstr(*split, "F"))
			len++;
		if (ft_strstr(*split, "C"))
			len++;
		free_texture(split);
	}
	return (len == 6);
}

int	check_insert_texture(t_cub3d *cubmap)
{
	int		i;
	char	**split;
	char	*tr;

	i = -1;
	while (cubmap->map[++i])
	{
		split = ft_split(cubmap->map[i], ' ');
		if (split[1])
		{
			tr = ft_strtrim(split[1], " \t\n");
			free (split[1]);
			split[1] = tr;
		}
		else
		{
			free_texture(split);
			break ;
		}
		add_textur(cubmap, split[1], *split);
		if (!check_colors(split, cubmap))
			return (free_texture(split), 0);
		free_texture(split);
	}
	return (check_doube_texture(cubmap->map));
}

void	replaced(char **map)
{
	int		i;
	char	*tmp;
	int		j;

	i = -1;
	while (map[++i])
	{
		tmp = ft_strtrim(map[i], " \t\n");
		j = 0;
		free(map[i]);
		while (tmp[j])
		{
			if (tmp[j] == '\t')
				tmp[j] = ' ';
			j++;
		}
		map[i] = tmp;
	}
}

int	read_file(char *file_name, t_cub3d *cubmap)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error read map !\n", 2), 0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error read map !\n", 2), 0);
	get_map(i, fd, cubmap);
	replaced(cubmap->map);
	close(fd);
	return (check_insert_texture(cubmap));
}
