/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dlc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		colors_init(t_map *map)
{
	map->colors[0] = 0xFF0000;
	map->colors[1] = 0x00FF00;
	map->colors[2] = 0x0000FF;
	map->colors[3] = 0x0575E3;
}

int			sprite_compare(void *entity1, void *entity2)
{
	return (((t_entity *)entity2)->dist - ((t_entity *)entity1)->dist);
}

void		map_load_entity(t_map *map, t_mapload *ml)
{
	ml->i = 0;
	while (ml->i < map->nb_entity)
	{
		read(ml->fd, &ml->tmp_x, sizeof(float));
		read(ml->fd, &ml->tmp_y, sizeof(float));
		map->entity[ml->i].pos.x = ml->tmp_x;
		map->entity[ml->i].pos.y = ml->tmp_y;
		map->entity[ml->i].dir.x = 1;
		map->entity[ml->i].dir.y = 0;
		read(ml->fd, &map->entity[ml->i].type, sizeof(Uint32));
		read(ml->fd, &map->entity[ml->i].texture, sizeof(Uint32));
		map->entity_ptr[ml->i] = &map->entity[ml->i];
		ml->i++;
	}
}

void		map_load_data(t_map *map, char *path, t_mapload *ml)
{
	ml->i = 0;
	map->textures = (SDL_Surface **)malloc(sizeof(SDL_Surface *)
			* map->nb_texture);
	while (ml->i < map->nb_texture)
	{
		ml->nb = ft_itoa(ml->i);
		ft_kebab(ml->buff, path, "textures/", ml->nb, ".bmp", NULL);
		map->textures[ml->i++] = SDL_LoadBMP(ml->buff);
		free(ml->nb);
	}
	colors_init(map);
	ft_kebab(ml->buff, path, "textures/sky.bmp", NULL);
	map->sky = SDL_LoadBMP(ml->buff);
	map->ceil = (Uint8 *)ft_malloc(sizeof(Uint8) * map->lx * map->ly);
	map->wall = (Uint8 *)ft_malloc(sizeof(Uint8) * map->lx * map->ly);
	map->floor = (Uint8 *)ft_malloc(sizeof(Uint8) * map->lx * map->ly);
	read(ml->fd, map->ceil, map->lx * map->ly);
	read(ml->fd, map->wall, map->lx * map->ly);
	read(ml->fd, map->floor, map->lx * map->ly);
}
