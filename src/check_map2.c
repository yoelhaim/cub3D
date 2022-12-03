/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/12/02 15:17:55 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_in_map(char c)
{
	char	*str;
	int		i;

	str = ft_strdup("01ENSW");
	i = -1;
	while (str[++i])
	{
		if (c == str[i])
			break ;
	}
	free(str);
	if (i == 6)
		return (0);
	return (1);
}

int	find_player_position( t_cub3d *cubmap)
{
	int	i;
	int	j;
	int	len;
	char **map;

	i = -1;
	len = 0;
	map = cubmap->maps;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E' || map[i][j] == 'N' \
			|| map[i][j] == 'S' || map[i][j] == 'W')
			{
				cubmap->pos_player_x = j;
				cubmap->pos_player_y = i;
				cubmap->direction = map[i][j];
				map[i][j] = '0';
				len++;
			}
			j++;
		}
	}
	if (len == 0 || len > 1)
		return (ft_putstr_fd("Error: player not exists or duplicated!\n", 2), 0);
	return (1);
}

int	check_first_last(char **tmp, int i)
{
	char *line;

	while (tmp[i])
	{
		line = ft_strtrim(tmp[i], " \t\n"); // error here -
		if (ft_strlen(line) == 0)
		{
			i++;
			continue ;
		}
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_spaces(int i, t_cub3d *cubmap)
{
	char	**map;
	int		j;
	
	map = cubmap->maps;
	if (!find_player_position(cubmap) || !check_first_last(map, i))
		return (0);
	i = 0;
	
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (!map[i + 1] || !map[i - 1])
					return (0);
				if (!check_in_map(map[i - 1][j]) \
				|| (!check_in_map(map[i + 1][j])) \
				|| !check_in_map(map[i][j + 1]) || !check_in_map(map[i][j - 1]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_is_valid(t_cub3d *cubmap)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	map = cubmap->maps;
	while (map[i][j] != '\n' && map[i][j])
	{
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] == ' ')
			i++;
		if (map[i][j] != '1')
			return (0);
		j++;
	}
	return (check_spaces(i, cubmap));
}
