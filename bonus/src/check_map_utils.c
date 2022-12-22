/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:38:24 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/22 14:36:27 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_exten(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	ft_is_digit(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && str[i] == '0')
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (1);
		len++;
		i++;
	}
	if (len > 3)
		return (1);
	free(str);
	return (0);
}

char	*rev_str(char *str)
{
	char	*buff;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str) - 1;
	buff = ft_calloc(len + 1, sizeof(char));
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
	char	*extenstion;

	extenstion = rev_str(filename);
	if (!ft_strcmp(extenstion, "buc"))
	{
		free(extenstion);
		return (1);
	}
	free(extenstion);
	return (0);
}

int	check_name_exc_texture(char *filename)
{
	int	equal;

	equal = !ft_strcmp(filename, "xpm");
	free(filename);
	return (equal);
}
