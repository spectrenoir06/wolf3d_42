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

void	hud_fill(t_game *game)
{
	int		x;
	int		y;
	t_color	c;

	c.r = 255;
	c.g = 0;
	c.b = 255;
	x = 0;
	while (x < game->sdl.lx)
	{
		y = 0;
		while (y < game->sdl.ly)
		{
			memcpy(&game->sdl.hud_buf[x + (y * game->sdl.lx)], &c, 3);
			y++;
		}
		x++;
	}
}

void	hud_cross(t_game *game)
{
	t_color color = {255, 0, 254};
	game_draw_rect(game, game->sdl.hud_buf, game->sdl.lx / 2 - 20, game->sdl.ly / 2 - 2, 10, 4, color);
	game_draw_rect(game, game->sdl.hud_buf, game->sdl.lx / 2 + 10, game->sdl.ly / 2 - 2, 10, 4, color);
	game_draw_rect(game, game->sdl.hud_buf, game->sdl.lx / 2 - 2, game->sdl.ly / 2 - 20, 4, 10, color);
	game_draw_rect(game, game->sdl.hud_buf, game->sdl.lx / 2 - 2, game->sdl.ly / 2 + 10, 4, 10, color);
}

void	hud_fps(t_game *game)
{
	t_color color = {255, 0, 254};

}

void	hud_render(t_game *game)
{
	hud_fill(game);
	map_draw(game);
	hud_cross(game);
	weapon_draw(game);
}

void	hud_put(t_game *game)
{
	int	x;
	int	y;
	t_color color;

	for(x = 0; x < game->sdl.lx; x++)
	{
		for(y = 0; y < game->sdl.ly; y++)
		{
			memcpy(&color, &game->sdl.hud_buf[x + (y * game->sdl.lx)], 3);
			if (!(color.r == 255 && color.g == 0 && color.b == 255))
				memcpy(&game->sdl.text_buf[x + (y * game->sdl.lx)], &game->sdl.hud_buf[x + (y * game->sdl.lx)], 3);
		}
	}
}
