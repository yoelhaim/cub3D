/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pro <pro@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/11/17 01:45:20 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int check_exten(char *filename)
{

	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	return (1);
}

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


char	**get_map(int size, int fd)
{
	char	**buff;
	int		length;

	length = -1;
	buff = malloc(sizeof(char *) * size + 1);
	while(++length < size)
		buff[length] =  get_next_line(fd);
	buff[length] = 0;
	close(fd);
	return (buff);
}

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

int check_colors(char **colors, t_cub3d *cubmap, int index)
{
	(void) cubmap;
	(void) index;

	if (strstr(*colors, "F") )
			printf("%s\n", colors[1]);
	if (strstr(*colors, "C") )
			printf("%s\n", colors[1]);
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
			break;
		if (strstr(*split, "NO") )
			cubmap->no = strdup(split[1]);
		else if (strstr(*split, "SO"))
			cubmap->so = strdup(split[1]);
		else if (strstr(*split, "WE"))
			cubmap->we = strdup(split[1]);
		else if (strstr(*split, "EA"))
			cubmap->ea = strdup(split[1]);
		check_colors(split, cubmap, i);
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

int read_to_file(char *namefile, t_cub3d *cubmap)
{
	int fd;
	char **map;
	(void) cubmap;

	int i;
	fd = open(namefile, O_RDONLY);
	if (fd < 0)
		return (printf("error read to map ! \n"), 0);
	i = 0;
	while(get_next_line(fd))
		i++;
	fd = open(namefile, O_RDONLY);
	map = get_map(i, fd);
	check_insert_texture(remove_empty_line(map), cubmap);
	return (1);
}

int main(int ac, char **av)
{
	char	*namefile;
	t_cub3d cubmap;

	if (ac != 2)
		return (printf("arg don't Valid"), 1);
	namefile = av[1];
	if (!check_exten(namefile))
		return (write(1, "error open  map !\n", 19), 1);
	else if (!check_name_exc(namefile))
		return (write(1, "error extention maps !\n", 24), 1);
	else
	{
		read_to_file(namefile, &cubmap);
		printf("Go! %s\n", cubmap.so);
		printf("Go! %s\n", cubmap.no);
		printf("Go! %s\n", cubmap.we);
		printf("Go! %s\n", cubmap.ea);
		printf("index ! %d\n", cubmap.last_index);
	}
}
