/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pro <pro@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/11/19 20:34:37 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void scq_map(t_cub3d *cubmap)
{
    int i;
    int j;
    size_t len;

    i = -1;
    len = ft_strlen(cubmap->maps[0]);
    while(cubmap->maps[++i])
    {j = -1;
        while(cubmap->maps[i][++j])
        if (cubmap->maps[i][j] == ' ' || cubmap->maps[i][j] == '\t')
            cubmap->maps[i][j] = '-';
        if (ft_strlen(cubmap->maps[i]) > len)
            len = ft_strlen(cubmap->maps[i]);
    }
}

int check_maps(t_cub3d *cubmap)
{
    int     i;
    char    **tmp;
    int j;
    
    j = 0;
    i =  -1;
    tmp = cubmap->map;
    while(tmp[++i])
    {
        if (strstr(tmp[i], "111") )
            break;
    }
    cubmap->maps = malloc(sizeof(char *) * ft_len_ptr(tmp) - cubmap->last_index);
   while(tmp[i])
    {
       cubmap->maps[j] = tmp[i];
       i++;
       j++;
    }
    cubmap->maps[j] = 0;
    scq_map(cubmap);
	return (1);
}

int check_is_valid_map(char **maps)
{
    int i = 0;
    int j = 0;
    char **tmp = maps;
    while(maps[i][j] != '\n' && maps[i][j])
    {
        while(maps[i][j] == '-')
            j++;
        if (maps[i][j] == '-')
            i++;
        if (maps[i][j] != '1')
        return (0);
        j++;
    }
    while(tmp[++i])
    {
        tmp[i] = ft_strtrim(tmp[i], "-");
        printf("%s\n", tmp[i]);
    }
    return (1);
}