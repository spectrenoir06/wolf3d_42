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

void		hud_background(t_game *game, int mode)
{
	SDL_Surface		*hud[4];
	int				i;
	char			*strmode;
	char			path[256];

	strmode = ft_itoa(mode);
	ft_kebab(path, "modes/", strmode, "/hud/top.bmp", NULL);
	hud[0] = SDL_LoadBMP(path);
	ft_kebab(path, "modes/", strmode, "/hud/left.bmp", NULL);
	hud[1] = SDL_LoadBMP(path);
	ft_kebab(path, "modes/", strmode, "/hud/right.bmp", NULL);
	hud[2] = SDL_LoadBMP(path);
	ft_kebab(path, "modes/", strmode, "/hud/bottom.bmp", NULL);
	hud[3] = SDL_LoadBMP(path);
	free(strmode);
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

int			bgr_average(int c1, int c2)
{
	int		r;
	int		g;
	int		b;

	r = ((c1 >> 16) & 0xFF) + ((c2 >> 16) & 0xFF);
	r = r >> 1;
	g = ((c1 >> 8) & 0xFF) + ((c2 >> 8) & 0xFF);
	g = g >> 1;
	b = (c1 & 0xFF) + (c2 & 0xFF);
	b = b >> 1;
	return ((b << 16) + (g << 8) + r);
}

void		hud_map(t_game *game)
{
	int		x;
	int		y;
	Uint32	color;
	Uint32	bcolor;

	x = 0;
	while (x < game->map.lx)
	{
		y = 0;
		while (y < game->map.ly)
		{
			color = (game->map.wall[x + (y * game->map.lx)] ? WALL : FLOOR);
			bcolor = ((Uint32 *)game->sdl.text_buf)[GAME_X + x * 4
					+ (GAME_Y + y * 4) * game->sdl.lx];
			color = bgr_average(color, bcolor);
			game_draw_rect(game, GAME_X + x * 4, GAME_Y + y * 4, color);
			y++;
		}
		x++;
	}
	game_draw_rect(game, GAME_X + game->player.pos.x * 4,
			GAME_Y + game->player.pos.y * 4, PLAYER);
	game_draw_rect(game, GAME_X + game->player.pos.x * 4
			+ (game->player.dir.x * 4), GAME_Y + game->player.pos.y * 4
			+ (game->player.dir.y * 4), FACE);
}
