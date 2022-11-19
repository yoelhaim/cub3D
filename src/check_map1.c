/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pro <pro@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:15:13 by pro               #+#    #+#             */
/*   Updated: 2022/11/19 20:43:32 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


char *rev_str(char *str)
{
	char *buff;
	int i;

	i = 0;
	buff = "";
	int len = strlen(str) - 1;
	buff = malloc(sizeof(char) * len + 1);
	while (len && str[len] != '.')
	{
		buff[i] = str[len];
		i++;
		len--;
	}
	buff[i] = 0;
	return (buff);
}

int check_name_exc(char *filename)
{
	if (strcmp(rev_str(filename), "buc"))
		return (0);
	return (1);
}


void get_map(int size, int fd, t_cub3d *cubmap)
{
	int		length;

	length = 0;
	cubmap->map = malloc(sizeof(char *) * size );
	while(length < size)
    {
		cubmap->map[length] =  get_next_line(fd);
        length++;
    }
	cubmap->map[length] = 0;
	close(fd);
}


int check_colors(char **colors, t_cub3d *cubmap, int index)
{
	(void) cubmap;
	(void) index;

	if (strstr(*colors, "F") )
	{
		if (!check_colors_floor(*(colors + 1), cubmap))
            return (0);
        
	}
			
	if (strstr(*colors, "C") )
			if (!check_colors_ciel(*(colors + 1), cubmap))
            	return (0);
	return (1);
}

int check_insert_texture(char **map, t_cub3d *cubmap)
{
	int		i;
	char	**split;

	i = -1;
	while (map[++i])
	{
		split = ft_split(map[i], ' ');
		if (split[1])
			split[1] = ft_strtrim(split[1], " \t\n");
		else
        {
            break;
        }
			
		if (strstr(*split, "NO") )
			cubmap->no = strdup(split[1]);
		else if (strstr(*split, "SO"))
			cubmap->so = strdup(split[1]);
		else if (strstr(*split, "WE"))
			cubmap->we = strdup(split[1]);
		else if (strstr(*split, "EA"))
			cubmap->ea = strdup(split[1]);
		if (!check_colors(split, cubmap, i))
			return (0);
		cubmap->last_index = i + 1;
		
	}
	return (1);
}
char  **remove_empty_line(char **map)
{
	int i=0;
	int j =0;
	
	char **tmp;
	while(map[i])
		i++;
	tmp = malloc(sizeof(char *) + i);
	i = 0;
	while(map[i])
	{
		map[i] = ft_strtrim(map[i], " \t\n");
		if (j == 6)
			break;
		if (ft_strlen(map[i]) != 0)
			tmp[j] = map[i];
		else
			j -= 1;
		j++;
		i++;
	}
	tmp[j] = 0;
	return(tmp);
}
void    replaced(char **maps)
{
    int i;
    int j;
    
    i = -1;
    
    while(maps[++i])
    {
        j =-1;
      while(maps[i][++j])
          {
            if (maps[i][j] == '\t')
                maps[i][j] = ' ';
        }
    }
}
int read_to_file(char *namefile, t_cub3d *cubmap)
{
	int fd;
	char **map;

	int i;
	fd = open(namefile, O_RDONLY);
	if (fd < 0)
		return (printf("error read to map ! \n"), 0);
	i = 0;
	while(get_next_line(fd))
		i++;
	fd = open(namefile, O_RDONLY);
    get_map(i, fd, cubmap);
    replaced(cubmap->map);
	map = cubmap->map;
	if (!check_insert_texture(remove_empty_line(map), cubmap))
		return (0);
	return (1);
}