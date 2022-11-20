/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/11/20 22:34:56 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char *rev_str(char *str)
{
	char *buff;
	int i;

	i = 0;
	buff = "";
	int len = strlen(str) - 1;
	buff = malloc(sizeof(char) * len + 1);
	while (len && str[len] != '.')
	{
		buff[i] = str[len];
		i++;
		len--;
	}
	buff[i] = 0;
	return (buff);
}

int check_name_exc(char *filename)
{
	return (!strcmp(rev_str(filename), "buc"));
}

void get_map(int size, int fd, t_cub3d *cubmap)
{
	int length;
	char *str;

	length = 0;
	cubmap->map = malloc(sizeof(char *) * size);
	while (length < size)
	{
		str = ft_strtrim(get_next_line(fd), " \t\n");
		if (strstr(str, "111"))
			break;
		if (ft_strlen(str) != 0)
			cubmap->map[length] = str;
		else
			length -= 1;
		length++;
	}

	cubmap->map[length] = 0;
	close(fd);
}

int check_colors(char **colors, t_cub3d *cubmap)
{
	if (strstr(*colors, "F"))
		return (check_colors_floor(*(colors + 1), cubmap));
	if (strstr(*colors, "C"))
		return (check_colors_ciel(*(colors + 1), cubmap));
	return (1);
}

int check_doube_texture(char **map)
{
	int i;
	char **split;
	int len;

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

int check_insert_texture(char **map, t_cub3d *cubmap)
{
	int i;
	char **split;

	i = -1;
	while (map[++i])
	{
		split = ft_split(map[i], ' ');
		if (split[1])
			split[1] = ft_strtrim(split[1], " \t\n");
		else
			break;
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

void replaced(char **maps)
{
	int i;
	int j;

	i = -1;

	while (maps[++i])
	{
		maps[i] = ft_strtrim(maps[i], " \t\n");
		j = -1;
		while (maps[i][++j])
		{
			if (maps[i][j] == '\t')
				maps[i][j] = ' ';
		}
	}
}
int read_to_file(char *namefile, t_cub3d *cubmap)
{
	int fd;
	char **map;

	int i;
	fd = open(namefile, O_RDONLY);
	if (fd < 0)
		return (printf("error read to map ! \n"), 0);
	i = 0;
	while (get_next_line(fd))
		i++;
	fd = open(namefile, O_RDONLY);
	get_map(i, fd, cubmap);
	replaced(cubmap->map);
	map = cubmap->map;
	return (check_insert_texture(map, cubmap));
}