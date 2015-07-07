/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:55:44 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/13 16:55:46 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		sprite_load(t_map *map, char *path)
{
	int		i;
	char	buff[256];
	char	*nb;

	i = 0;
	while (i < map->nb_sprite)
	{
		nb = ft_itoa(i);
		ft_kebab(buff, path, "sprites/", nb, ".bmp", NULL);
		map->sprite[i].tex = SDL_LoadBMP(buff);
		map->sprite[i].frames = map->sprite[i].tex->w / TEX_SIZE;
		free(nb);
		i++;
	}
}

void		map_init(t_game *game, int mode, int map)
{
	int		x;
	char	path[256];
	char	*strmode;
	char	*strmap;

	strmode = ft_itoa(mode);
	strmap = ft_itoa(map);
	ft_kebab(path, "modes/", strmode, "/maps/", strmap, "/", NULL);
	free(strmode);
	free(strmap);
	map_load(&(game->map), path);
	sprite_load(&(game->map), path);
	weapon_load(&(game->map), path, 1);
	x = 0;
	while (x < 10)
		game->input[x++] = 0;
	player_init(game);
	hud_background(game, mode);
	game_init_sdl_mixer(&game->sounds, path);
}

int			map_load(t_map *map, char *path)
{
	t_mapload	ml;

	ft_kebab(ml.buff, path, "map.bin", NULL);
	if ((ml.fd = open(ml.buff, O_RDONLY)) == -1)
		return (-1);
	read(ml.fd, &(map->lx), 4);
	read(ml.fd, &(map->ly), 4);
	read(ml.fd, &(map->nb_entity), 4);
	read(ml.fd, &map->nb_texture, 4);
	read(ml.fd, &map->nb_sprite, 4);
	read(ml.fd, &map->start_x, 4);
	read(ml.fd, &map->start_y, 4);
	read(ml.fd, &map->has_fc, 4);
	map_load_data(map, path, &ml);
	map_load_entity(map, &ml);
	return (1);
}

void		map_unload(t_map *map)
{
	int		i;

	i = 0;
	free(map->floor);
	free(map->wall);
	free(map->ceil);
	while (i < map->nb_texture)
		SDL_FreeSurface(map->textures[i++]);
	i = 0;
	while (i < map->nb_sprite)
		SDL_FreeSurface(map->sprite[i++].tex);
	free(map->textures);
	SDL_FreeSurface(map->sky);
}

int			map_get_block(t_map *map, uint8_t *data, t_vect2dd pt)
{
	return (data[((int)pt.x) + ((int)pt.y) * map->lx]);
}
