/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/12/18 21:51:20 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_colors(char **colors, t_cub3d *cubmap)
{
	if (ft_strstr(*colors, "F"))
		return (check_colors_floor(*(colors + 1), cubmap));
	if (ft_strstr(*colors, "C"))
		return (check_colors_ciel(*(colors + 1), cubmap));
	return (1);
}
void free_texture(char **split)
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

	i = -1;
	while (cubmap->map[++i])
	{
		split = ft_split(cubmap->map[i], ' ');
		if (split[1])
		{
			char *tr = ft_strtrim(split[1], " \t\n");
			free(split[1]);
			split[1] = tr;
		}
		else
		{
			free_texture(split);
			break ;
		}
		if (ft_strstr(*split, "NO"))
		cubmap->no = ft_strdup(split[1]);
		else if (ft_strstr(*split, "SO"))
			cubmap->so = ft_strdup(split[1]);
		else if (ft_strstr(*split, "WE"))
			cubmap->we = ft_strdup(split[1]);
		else if (ft_strstr(*split, "EA"))
			cubmap->ea = ft_strdup(split[1]);
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
