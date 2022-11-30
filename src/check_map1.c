/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/11/30 19:01:26 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_colors(char **colors, t_cub3d *cubmap)
{
	if (strstr(*colors, "F"))
		return (check_colors_floor(*(colors + 1), cubmap));
	if (strstr(*colors, "C"))
		return (check_colors_ciel(*(colors + 1), cubmap));
	return (1);
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
		if (strstr(*split, "SO"))
			len++;
		if (strstr(*split, "NO"))
			len++;
		if (strstr(*split, "EA"))
			len++;
		if (strstr(*split, "WE"))
			len++;
		if (strstr(*split, "F"))
			len++;
		if (strstr(*split, "C"))
			len++;
	}
	if (len != 6)
		return (0);
	return (1);
}

int	check_insert_texture(char **map, t_cub3d *cubmap)
{
	int		i;
	char	**split;

	i = -1;
	while (map[++i])
	{
		split = ft_split(map[i], ' ');
		if (split[1])
			split[1] = ft_strtrim(split[1], " \t\n");
		else
			break ;
		if (strstr(*split, "NO"))
			cubmap->no = strdup(split[1]);
		else if (strstr(*split, "SO"))
			cubmap->so = strdup(split[1]);
		else if (strstr(*split, "WE"))
			cubmap->we = strdup(split[1]);
		else if (strstr(*split, "EA"))
			cubmap->ea = strdup(split[1]);
		if (!check_colors(split, cubmap))
			return (0);
		cubmap->last_index = i + 1;
	}
	return (check_doube_texture(map));
}

void	replaced(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		map[i] = ft_strtrim(map[i], " \t\n");
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '\t')
				map[i][j] = ' ';
		}
	}
}

int	read_to_file(char *file_name, t_cub3d *cubmap)
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
	return (check_insert_texture(cubmap->map, cubmap));
}
