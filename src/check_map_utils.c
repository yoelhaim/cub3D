/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:38:24 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/11/22 15:43:21 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_errors(char **value)
{
	int	fd;

	if (!value)
		return (ft_putstr_fd("error\n", 2), 0);
	if (ft_strlen(value[0]) != 2)
		return (ft_putstr_fd("error name\n", 2), 0);
	fd = open(ft_strtrim((strstr(value[0], "./") + 2), "\n"), O_RDONLY);
	if (fd < 0)
		return (printf("error open texture  %s\n", value[0]), 0);
	return (1);
}

int	check_exten(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	return (1);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (1);
	}
	return (0);
}

char	*rev_str(char *str)
{
	char	*buff;
	int		i;
	int		len;

	i = 0;
	buff = "";
	len = strlen(str) - 1;
	buff = malloc(sizeof(char) * len + 1);
	if (!buff)
		return (0);
	while (len && str[len] != '.')
	{
		buff[i] = str[len];
		i++;
		len--;
	}
	buff[i] = 0;
	return (buff);
}

int	check_name_exc(char *filename)
{
	return (!strcmp(rev_str(filename), "buc"));
}
