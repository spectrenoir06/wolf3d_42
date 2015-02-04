/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void		hud_background(t_game *game)
{
	SDL_Surface		*hud[4];
	int				i;

	hud[0] = SDL_LoadBMP("modes/1/hud/top.bmp");
	hud[1] = SDL_LoadBMP("modes/1/hud/left.bmp");
	hud[2] = SDL_LoadBMP("modes/1/hud/right.bmp");
	hud[3] = SDL_LoadBMP("modes/1/hud/bottom.bmp");
	bmp_draw(game, hud[0], 0, 0);
	bmp_draw(game, hud[1], 0, 20);
	bmp_draw(game, hud[2], game->sdl.lx - 40, 20);
	bmp_draw(game, hud[3], 0, game->sdl.ly - 220);
	i = 0;
	while (i < 4)
		SDL_FreeSurface(hud[i++]);
}

void		hud_render(t_game *game)
{
	hud_map(game);
	weapon_animate(game, &game->player);
	weapon_draw(game);
}

void		hud_map(t_game *game)
{
	int			x;
	int			y;

	x = 0;
	while (x < game->map.lx)
	{
		y = 0;
		while (y < game->map.ly)
		{
			game_draw_rect(game, game->sdl.text_buf, x * 4, y * 4,
					(game->map.wall[x + (y * game->map.lx)] ? WALL : FLOOR));
			y++;
		}
		x++;
	}
	game_draw_rect(game, game->sdl.text_buf, game->player.pos.x * 4,
			game->player.pos.y * 4, PLAYER);
	game_draw_rect(game, game->sdl.text_buf,
			game->player.pos.x * 4 + (game->player.dir.x * 4),
			game->player.pos.y * 4 + (game->player.dir.y * 4),
			FACE);
}
