/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		weapon_load(t_map *map, char *path, int n)
{
	int		i;
	int		j;
	char	buff[255];
	char	*nbi;
	char	*nbj;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < 5)
		{
			nbi = ft_itoa(i + 1);
			nbj = ft_itoa(j + 1);
			ft_kebab(buff, path, "weapons/", nbi, "/", nbj, ".bmp", NULL);
			ft_putendl(buff);
			map->weapon_tex[i + 1][j] = SDL_LoadBMP(buff);
			free(nbi);
			free(nbj);
			j++;
		}
		i++;
	}
	return (1);
}

void	weapon_unload(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 5)
		SDL_FreeSurface(map->weapon_tex[1][i + 1]);
}

void	weapon_start_anim(t_game *game, t_player *player)
{
	player->w_anim = 1.0;
	weapon_animate(game, player);
}

int		weapon_animate(t_game *game, t_player *player)
{
	float	last;

	last = player->w_anim;
	if (player->w_anim > 0)
		player->w_anim += game->dt * 15;
	if (player->w_anim > 5)
		player->w_anim = 0;
	return ((int)last != (int)player->w_anim);
}

void	weapon_draw(t_game *game)
{
	int	weapon;
	int	anim;

	weapon = (int)game->player.weapon;
	anim = (int)(game->player.w_anim);
	bmp_draw(game,
			game->map.weapon_tex[weapon][anim],
			game->sdl.lx / 2 - 256, (game->sdl.ly - 512 - 220));
}
