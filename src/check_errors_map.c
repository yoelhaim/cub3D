/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pro <pro@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/11/18 22:53:03 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int check_errors(char **value)
{
	int fd;
	if(!value)
		return(printf("error\n"), 0);
	if (ft_strlen(value[0]) != 2)
		return(printf("error name \n"), 0);
	fd = open (ft_strtrim((strstr(value[0], "./") + 2), "\n"), O_RDONLY);
	if (fd < 0)
		return(printf("error open texture  %s\n", value[0]), 0);
	
	return (1);
}


int check_exten(char *filename)
{

	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	return (1);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = -1;
	while(str[++i])
	{
		if ((str[i] < '0' || str[i] > '9') )
			return (1);
	}
	return (0);
}

int check_colors_floor(char *color, t_cub3d *cubmap)
{
    char **splited;
    int i;

    i = 0;
    
    splited = ft_split(color, ',');
    while(splited[i])
    {
        if (ft_is_digit(ft_strtrim(splited[i], " ")))
			return (0);
         i++;
    }
       
    if (i != 3)
        return (0);
    i = -1;
    while(color[++i])
    {
        if (color[i] == ',' && color[i + 1] == ',')
            return (0);
    }
    cubmap->floor[0] = atoi(splited[0]);
    cubmap->floor[1] = atoi(splited[1]);
    cubmap->floor[2] = atoi(splited[2]);
    return (1);
}


int check_colors_ciel(char *color, t_cub3d *cubmap)
{
        char **splited;
    int i;

    i = 0;
    
    splited = ft_split(color, ',');
    while(splited[i])
	{
		 if (ft_is_digit(ft_strtrim(splited[i], " ")))
			return (0);
        i++;
	}
    if (i != 3)
        return (0);
    i = -1;
    while(color[++i])
    {
        if (color[i] == ',' && color[i + 1] == ',')
            return (0);
    }
    cubmap->ciel[0] = atoi(splited[0]);
    cubmap->ciel[1] = atoi(splited[1]);
    cubmap->ciel[2] = atoi(splited[2]);
    return (1);
}
 int check_floor_ceil(int *str)
 {
	 int	i;

	 i=0;
	 while(i < 3)
	 {
		 if (str[i] < 0 || str[i] > 255)
		 	return (0);
		 i++;
	 }
	 return (1);
 }
 int is_open(char *namefile)
 {
	 int	fd;
	 
	 fd = open(namefile, O_RDONLY);
	 close(fd);
	 return (fd);
 }
 int check_file_texture(t_cub3d *texture)
 {
	 if (is_open(texture->no) == -1 || is_open(texture->so) == -1 || is_open(texture->ea) == -1 || is_open(texture->we) == -1)
	 	return (0);
	return (1);
 }