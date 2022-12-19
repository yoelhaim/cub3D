/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:32:13 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/19 16:07:44 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_colors_floor(char *color, t_cub3d *cubmap)
{
	char	**splited;
	int		i;

	i = 0;
	splited = ft_split(color, ',');
	while (splited[i])
	{
		if (ft_is_digit(ft_strtrim(splited[i], " ")))
			return (ft_putendl_fd("Error\nColor not valide!", 2), 0);
		i++;
	}
	if (i != 3)
		return (0);
	i = -1;
	while (color[++i])
	{
		if (color[i] == ',' && color[i + 1] == ',')
			return (ft_putendl_fd("Error\nColor not valide!", 2), 0);
	}
	cubmap->floor[0] = ft_atoi(splited[0]);
	cubmap->floor[1] = ft_atoi(splited[1]);
	cubmap->floor[2] = ft_atoi(splited[2]);
	free_texture(splited);
	return (1);
}

int	check_colors(char **colors, t_cub3d *cubmap)
{
	if (ft_strstr(*colors, "F"))
		return (check_colors_floor(*(colors + 1), cubmap));
	if (ft_strstr(*colors, "C"))
		return (check_colors_ciel(*(colors + 1), cubmap));
	return (1);
}

void	add_textur(t_cub3d *cubmap, char *split, char *find)
{
	if (ft_strstr(find, "NO"))
		cubmap->no = ft_strdup(split);
	else if (ft_strstr(find, "SO"))
		cubmap->so = ft_strdup(split);
	else if (ft_strstr(find, "WE"))
		cubmap->we = ft_strdup(split);
	else if (ft_strstr(find, "EA"))
		cubmap->ea = ft_strdup(split);
}

int	add_textur_color(char **cubmap, int fd, int size, int last_size)
{
	int		length;
	char	*str;
	char	*line;

	length = 0;
	while (length < size)
	{
		if (length >= 6)
			break ;
		line = get_next_line(fd);
		str = ft_strtrim(line, " \t\n");
		if (ft_strlen(str) != 0)
			cubmap[length] = str;
		else
		{
			free(str);
			length -= 1;
		}
		free(line);
		length++;
		last_size++;
	}
	return (last_size);
}

void	setup_player(char c, int pos_x, int pos_y, t_cub3d *cubmap)
{
	cubmap->pos_player_x = pos_x;
	cubmap->pos_player_y = pos_y;
	cubmap->direction = c;
}
