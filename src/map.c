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
#include "libft.h"
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

void	map_init(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	y = 0;

	map_load(game, &(game->map), "modes/1/maps/1/map.bin");

	x = 0;

	while (x < 10)
	{
		game->input[x++] = 0;
	}

	t_vect2dd vect = {2.0, 2.0};
	t_sprite sprite = {vect, 0};
	game->map.sprite[0] = sprite;

}

void	map_draw(t_game *game)
{
	int x = 0;
	int y = 0;

	t_color		sol = {255, 000, 000, 00};
	t_color		mur = {000, 255, 000, 000};
	t_color		perso = {000, 000, 255, 000};
	t_color		face = {000, 100, 255, 000};

	while (x < game->map.lx)
	{
		y = 0;
		while (y < game->map.ly)
		{
			game_draw_rect(game, x * 4, y * 4, 4, 4, (game->map.data[x + (y * game->map.lx)] ? mur : sol));
			y++;
		}
		x++;
	}
	game_draw_rect(game, game->player.pos.x * 4, game->player.pos.y * 4, 2 , 2, perso);
	game_draw_rect(game, game->player.pos.x * 4 + (game->player.dir.x * 4), game->player.pos.y * 4 + (game->player.dir.y * 4), 2 , 2, face);
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
	if ((ret = read(fd, &(map->lx), 4)) <= 0)
		return (ret);
	if ((ret = read(fd, &(map->ly), 4)) <= 0)
		return (ret);
	if ((ret = read(fd, &textures, 4)) <= 0)
		return (ret);
	i = 0;
	while (i < textures)
	{
		ft_kebab(buff, "modes/1/maps/1/textures/", ft_itoa(i), ".bmp", NULL);
		map->textures[i] = SDL_LoadBMP(buff);
		i++;
	}
	map->data = (Uint8 *)malloc(sizeof(Uint8) * map->lx * map->ly);
	i = 0;
	while ((ret = read(fd, &buff, 255)) > 0)
	{
		buff[255] = 0;
		ft_memcpy(map->data + i, buff, ret);
		i += ret;
	}
	return (1);
}

int		map_get_block(t_map *map, t_vect2dd pt)
{
	return (map->data[(int)trunc(pt.x) + (int)trunc(pt.y) * map->lx]);
}
