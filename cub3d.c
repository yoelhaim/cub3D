/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pro <pro@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/11/05 16:44:21 by pro              ###   ########.fr       */
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

int main(int ac, char **av)
{

    if (ac != 2)
        return (1);
    if (!check_exten(av[1]))
        return (write(1, "error open  map !\n", 19), 1);
    else if (!check_name_exc(av[1]))
        return (write(1, "error extention maps !\n", 24), 1);
}