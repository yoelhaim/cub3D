/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/11/21 15:27:30 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_in_map(char c)
{
	char	*str;
	int		i;

	str = "01ENSW";
	i = -1;
	while (str[++i])
	{
		if (c == str[i])
			break ;
	}
	if (i == 6)
		return (0);
	return (1);
}

int	find_player_position(char **map, t_cub3d *cubmap)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = 0;
	j = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
			{
				cubmap->pos_player_x = i;
				cubmap->pos_player_y = j;
				map[i][j] = '0';
				len++;
			}
			j++;
		}
	}
	if (len == 0 || len > 1)
		return (printf("error find Player or duplicated!\n"), 0);
	return (1);
}

int	check_first_last(char **tmp, int i)
{
	while (tmp[i])
	{
		tmp[i] = ft_strtrim(tmp[i], " -\t\n");
		if (ft_strlen(tmp[i]) == 0)
		{
			i++;
			continue ;
		}
		if (tmp[i][0] != '1' || tmp[i][ft_strlen(tmp[i]) - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	more_valid_map(char **tmp, int i, t_cub3d *cubmap)
{
	char	**tmp2;
	int		j;

	i = 0;
	tmp2 = tmp;
	j = 0;
	if (!find_player_position(tmp, cubmap))
		return (0);
	while (tmp2[i])
	{
		j = 0;
		while (tmp2[i][j])
		{
			if (tmp2[i][j] == '0')
			{
				if (!check_in_map(tmp[i - 1][j]) \
				|| !check_in_map(tmp[i + 1][j]) \
				|| !check_in_map(tmp[i][j + 1]) || !check_in_map(tmp[i][j - 1]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (check_first_last(tmp, i));
}

int	check_is_valid_map(char **maps, t_cub3d *cubmap)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = maps;
	while (maps[i][j] != '\n' && maps[i][j])
	{
		while (maps[i][j] == '-')
			j++;
		if (maps[i][j] == '-')
			i++;
		if (maps[i][j] != '1')
			return (0);
		j++;
	}
	return (more_valid_map(tmp, i, cubmap));
}
