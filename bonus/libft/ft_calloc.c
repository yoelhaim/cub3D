/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:25:57 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/22 14:36:27 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	if (n == 0)
		return ;
	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	n;

	n = size * count;
	p = malloc(n);
	if (!p)
		exit (1);
	ft_bzero(p, n);
	return (p);
}
