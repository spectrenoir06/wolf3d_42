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

void	sprite_load(t_map *map, char *path)
{
	int		i;
	char	buff[256];
	char	*nb;

	i = 0;
	while (i < NB_SPRITE_TEX)
	{
		nb = ft_itoa(i);
		ft_kebab(buff, path, "sprites/", nb, ".bmp", NULL);
		map->sprite[i].tex = SDL_LoadBMP(buff);
		map->sprite[i].frames = map->sprite[i].tex->w / TEX_SIZE;
		free(nb);
		i++;
	}
}

void	map_init(t_game *game, int mode, int map)
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
	player_init(&game->player);
}

int		map_load(t_map *map, char *path)
{
	int		i;
	int		fd;
	char	buff[256];
	char	*nb;

	ft_kebab(buff, path, "map.bin", NULL);
	if ((fd = open(buff, O_RDONLY)) == -1)
		return (-1);
	read(fd, &(map->lx), 4);				// load lx
	read(fd, &(map->ly), 4);				// load ly
	read(fd, &(map->nb_entity), 4);			// load entity initial
	read(fd, &map->nb_texture, 4);					// load nb texture
	i = 0;
	map->textures = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * map->nb_texture);
	while (i < map->nb_texture)
	{
		nb = ft_itoa(i);
		ft_kebab(buff, path, "textures/", nb, ".bmp", NULL);
		map->textures[i] = SDL_LoadBMP(buff);
		free(nb);
		i++;
	}
	ft_kebab(buff, path, "textures/sky.bmp", NULL);
	map->sky = SDL_LoadBMP(buff);

	map->ceil	= (Uint8 *)ft_malloc(sizeof(Uint8) * map->lx * map->ly);
	map->wall	= (Uint8 *)ft_malloc(sizeof(Uint8) * map->lx * map->ly);
	map->floor	= (Uint8 *)ft_malloc(sizeof(Uint8) * map->lx * map->ly);

	printf("entity number = %d\n", map->nb_entity);
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
	while (i < map->nb_entity)
	{
		read(fd, &tmp_x, sizeof(float));
		read(fd, &tmp_y, sizeof(float));
		map->entity[i].pos.x = tmp_x;
		map->entity[i].pos.y = tmp_y;
		map->entity[i].dir.x = 1;
		map->entity[i].dir.y = 0;
		read(fd, &map->entity[i].type, sizeof(Uint32));
		read(fd, &map->entity[i].texture, sizeof(Uint32));

		printf("entity x = %f\n", tmp_x);
		printf("entity y = %f\n", tmp_y);
		printf("type entity = %d\n",map->entity[i].type);
		printf("tex entity = %d\n",map->entity[i].texture);
		map->entity_ptr[i] = &map->entity[i];
		i++;
	}
	return (1);
}

void	map_unload(t_map *map)
{
	int		i;

	i = 0;
	free(map->floor);
	free(map->wall);
	free(map->ceil);
	while (i < map->nb_texture)
		SDL_FreeSurface(map->textures[i]);
	free(map->textures);
	SDL_FreeSurface(map->sky);
	//map = NULL;
}

inline int		map_get_block(t_map *map, Uint8 *data, t_vect2dd pt)
{
	return (data[((int)pt.x) + ((int)pt.y) * map->lx]);
}
