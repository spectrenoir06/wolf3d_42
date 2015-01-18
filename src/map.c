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
	int		ret;
	int		info[3];
	char	buff[256];

	if ((fd = open(path, O_RDONLY)) == 0)
		return (-1);
	if ((ret = read(fd, &info, 3 * sizeof(int))) == 0)
		return (-1);
	game->map.lx = info[0];
	game->map.ly = info[1];
	i = 0;
	while (i < info[2])
	{
		ft_kebab(buff, "img/", ft_itoa(i), ".bmp", NULL);
		game->map.textures[i] = SDL_LoadBMP(buff);
		i++;
	}
}
