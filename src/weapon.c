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

int		weapon_load(t_game *game, t_map *map, int n)
{
//	int	i;
//	int	j;
//	char	buff[255];
//
//	i = 1;
//	while (i <= n)
//	{
//		j = 1;
//		while (j <= 5)
//		{
//			ft_kebab(buff, "modes/1/maps/1/weapons/", "1", "/", ft_itoa(j), ".bmp", NULL);
//			ft_putstr(buff);
//			map->weapon_tex[i][j] = SDL_LoadBMP(buff);
//			j++;
//		}
//		i++;
//	}
	map->weapon_tex[1][0] = SDL_LoadBMP("modes/1/maps/1/weapons/1/1.bmp");
	map->weapon_tex[1][1] = SDL_LoadBMP("modes/1/maps/1/weapons/1/2.bmp");
	map->weapon_tex[1][2] = SDL_LoadBMP("modes/1/maps/1/weapons/1/3.bmp");
	map->weapon_tex[1][3] = SDL_LoadBMP("modes/1/maps/1/weapons/1/4.bmp");
	map->weapon_tex[1][4] = SDL_LoadBMP("modes/1/maps/1/weapons/1/5.bmp");
	return (1);
}

void	weapon_start_anim(t_game *game, t_player *player)
{
	player->w_anim = 0.1;
	weapon_animate(game, player);
}

void	weapon_animate(t_game *game, t_player *player)
{
	if (player->w_anim > 0)
		player->w_anim += game->dt * 10;
	if (player->w_anim > 5)
		player->w_anim = 0;
	//printf("%=f \n", player->w_anim);
}

int		weapon_get_anim(t_player *player)
{
	return (int)(player->w_anim);
}

void	weapon_draw(t_game *game)
{
	int	x;
	int	y;
	t_color color;

	for(x = 0; x < 512; x++)
	{
		for(y = 0; y < 512; y++)
		{
			memcpy(&color, &((Uint8 *)game->map.weapon_tex[game->player.weapon][weapon_get_anim(&game->player)]->pixels)[x * 3 + (y * 3 * 512)], 3);
			if (!(color.r == 255 && color.g == 0 && color.b == 255))
				memcpy(&game->sdl.hud_buf[x + game->sdl.lx / 2 - 256 + ((y + game->sdl.ly - 512) * game->sdl.lx)], &((Uint8 *)game->map.weapon_tex[game->player.weapon][weapon_get_anim(&game->player)]->pixels)[x * 3 + (y * 3* 512)], 3);
		}
	}
}
