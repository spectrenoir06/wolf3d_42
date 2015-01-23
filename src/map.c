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

void	sprite_load(t_game *game, t_map *map)
{
	int		i;
	char	buff[256];

	i = 0;
	while (i < NBSPRITETEX)
	{
		ft_kebab(buff, "modes/1/maps/1/sprites/", ft_itoa(i), ".bmp", NULL);
		map->sprite_tex[i] = SDL_LoadBMP(buff);
		i++;
	}
}

void	map_init(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	y = 0;

	map_load(game, &(game->map), "modes/1/maps/1/map.bin");
	sprite_load(game, &(game->map));

	x = 0;

	while (x < 10)
	{
		game->input[x++] = 0;
	}

	x = 0;

	while (x < game->map.nb_obj)
	{
		game->map.sprite_ptr[x] = &game->map.sprite[x];
		x++;
	}
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
			game_draw_rect(game, game->sdl.hud_buf, x * 4, y * 4, 4, 4, (game->map.wall[x + (y * game->map.lx)] ? mur : sol));
			y++;
		}
		x++;
	}
	game_draw_rect(game, game->sdl.hud_buf, game->player.pos.x * 4, game->player.pos.y * 4, 2 , 2, perso);
	game_draw_rect(game, game->sdl.hud_buf, game->player.pos.x * 4 + (game->player.dir.x * 4), game->player.pos.y * 4 + (game->player.dir.y * 4), 2 , 2, face);
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
	if ((ret = read(fd, &(map->nb_obj), 4)) <= 0)
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
	map->sky = SDL_LoadBMP("modes/1/maps/1/textures/sky.bmp");

	map->ceil = (Uint8 *)ft_malloc(sizeof(Uint8) * map->lx * map->ly);
	map->wall = (Uint8 *)ft_malloc(sizeof(Uint8) * map->lx * map->ly);
	map->floor = (Uint8 *)ft_malloc(sizeof(Uint8) * map->lx * map->ly);

	map->sprite = (t_sprite *)ft_malloc(sizeof(t_sprite) * map->nb_obj);
	map->sprite_ptr = (t_sprite **)ft_malloc(sizeof(t_sprite * ) * map->nb_obj);
	printf("nb obj = %d\n", map->nb_obj);
	i = 0;
	while (i < (map->lx * map->ly))
	{
		read(fd, &map->ceil[i], 1);
		i++;
	}
	i = 0;
	while (i < (map->lx * map->ly))
	{
		read(fd, &map->wall[i], 1);
		i++;
	}
	i = 0;
	while (i < (map->lx * map->ly))
	{
		read(fd, &map->floor[i], 1);
		i++;
	}


	float tmp_x;
	float tmp_y;

	i = 0;
	while (i < map->nb_obj)
	{

		read(fd, &tmp_x, sizeof(float));
		read(fd, &tmp_y, sizeof(float));
		map->sprite[i].pos.x = tmp_x;
		map->sprite[i].pos.y = tmp_y;
		read(fd, &map->sprite[i].type, sizeof(Uint32));
		read(fd, &map->sprite[i].texture, sizeof(Uint32));

		printf("x obj = %f\n", tmp_x);
		printf("y obj = %f\n", tmp_y);
		printf("type obj = %d\n",map->sprite[i].type);
		printf("text obj = %d\n",map->sprite[i].texture);

		i++;
	}
	weapon_load(game, map, 1);
	return (1);
}

int		map_get_block(t_map *map, Uint8 *data, t_vect2dd pt)
{
	return (data[(int)trunc(pt.x) + (int)trunc(pt.y) * map->lx]);
}
