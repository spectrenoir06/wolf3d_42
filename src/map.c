/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:55:44 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/13 16:55:46 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>

void	ft_kebab(char * buff, const char * first, ...)
{
	int			i;
	int			j;
	const char	*next;
	va_list		lst;

	va_start(lst, first);
	next = first;
	i = 0;
	while(next != NULL)
	{
		j = 0;
		while (next[j] != 0)
		{
			buff[i] = next[j];
			i++;
			j++;
		}
		next = va_arg(lst, char*);
	}
	va_end(lst);
	buff[i] = 0;
}

int		map_load(t_game *game, t_map *map, char *path)
{
	int		i;
	int		fd;
	Uint32	textures;
	int		ret;
	char	buff[256];

	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	if ((ret = read(fd, &(map->lx), sizeof(Uint32))) <= 0)
		return (ret);
	if ((ret = read(fd, &(map->ly), sizeof(Uint32))) <= 0)
		return (ret);
	if ((ret = read(fd, &textures, sizeof(Uint32))) <= 0)
		return (ret);
	i = 0;
	while (i < textures)
	{
		ft_kebab(buff, "img/", ft_itoa(i), ".bmp", NULL);
		map->textures[i] = SDL_LoadBMP(buff);
		i++;
	}
	map->data = (Uint8 *)malloc(sizeof(Uint8) * map->lx * map->ly);
	if ((ret = read(fd, &(map->data), sizeof(Uint8) * map->lx * map->ly)) <= 0)
		return (ret);
	return (1);
}
