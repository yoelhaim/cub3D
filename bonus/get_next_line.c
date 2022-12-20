/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:10:19 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/20 21:30:27 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000000000
#endif

char	*ft_after(char *str)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	rest = malloc((ft_strlen(str) - i) + 1);
	if (!rest)
		return (NULL);
	j = 0;
	while (str[i])
		rest[j++] = str[i++];
	rest[j] = '\0';
	free(str);
	return (rest);
}

char	*ft_before(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

int	findnl(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*ft_read(int fd, char *buf, char *str)
{
	char	*tmp;
	int		i;

	i = 1;
	while (!findnl(str) && i != 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = '\0';
		tmp = str;
		if (!tmp)
		{
			tmp = malloc(1 * sizeof(char));
			tmp[0] = '\0';
		}
		str = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;
	char		*line;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE < 1)
	{
		free(buf);
		return (NULL);
	}
	str = ft_read(fd, buf, str);
	if (!str)
		return (NULL);
	line = ft_before(str);
	str = ft_after(str);
	return (line);
}
