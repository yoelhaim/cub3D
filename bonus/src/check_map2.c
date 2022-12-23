/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/12/23 15:18:19 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
	int		i;
	int		j;
	int		len;

	i = -1;
	len = 0;
	while (cubmap->maps[++i])
	{
		j = 0;
		while (cubmap->maps[i][j])
		{
			if (cubmap->maps[i][j] == 'E' || cubmap->maps[i][j] == 'N' \
			|| cubmap->maps[i][j] == 'S' || cubmap->maps[i][j] == 'W')
			{
				setup_player(cubmap->maps[i][j], j, i, cubmap);
				cubmap->maps[i][j] = '0';
				len++;
			}
			j++;
		}
	}
	if (len == 0 || len > 1)
		return (ft_putstr_fd("Error\nplayer not exists or duplicated ❌\n", 2), 0);
	return (1);
}

int	check_first_last(char **tmp, int i)
{
	char	*line;

	while (tmp[i])
	{
		line = ft_strtrim(tmp[i], " \t\n");
		if (ft_strlen(line) == 0)
		{
			i++;
			continue ;
		}
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
			return (ft_putendl_fd("Error\nmap not allowed ❌!", 2), 0);
		free((line));
		i++;
	}
	return (1);
}

int	check_spaces(int i, t_cub3d *cubmap)
{
	int		j;

	i = 0;
	if (!find_player_position(cubmap) || !check_first_last(cubmap->maps, i))
		exit (1);
	while (cubmap->maps[i])
	{
		j = 0;
		while (cubmap->maps[i][j])
		{
			if (cubmap->maps[i][j] == '0')
			{
				if (!cubmap->maps[i + 1] || !cubmap->maps[i - 1])
					return (ft_putendl_fd("Error\nMap ❌!", 2), 0);
				if (!check_in_map(cubmap->maps[i - 1][j]) \
				|| (!check_in_map(cubmap->maps[i + 1][j])) \
				|| !check_in_map(cubmap->maps[i][j + 1]) || \
				!check_in_map(cubmap->maps[i][j - 1]))
					return (ft_putendl_fd("Error\nMap ❌!", 2), 0);
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
		if (map[i][j] != '1')
			return (ft_putendl_fd("Error\nmap not allowed ❌!", 2), 0);
		j++;
	}
	return (check_spaces(i, cubmap));
}
