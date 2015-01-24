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


void	hud_cross(t_game *game)
{
	t_color color = {255, 0, 254};
	game_draw_rect(game, game->sdl.text_buf, game->sdl.lx / 2 - 20, game->sdl.ly / 2 - 2, 10, 4, color);
	game_draw_rect(game, game->sdl.text_buf, game->sdl.lx / 2 + 10, game->sdl.ly / 2 - 2, 10, 4, color);
	game_draw_rect(game, game->sdl.text_buf, game->sdl.lx / 2 - 2, game->sdl.ly / 2 - 20, 4, 10, color);
	game_draw_rect(game, game->sdl.text_buf, game->sdl.lx / 2 - 2, game->sdl.ly / 2 + 10, 4, 10, color);
}

void	hud_fps(t_game *game)
{
	t_color color = {255, 0, 254};

}

void	hud_render(t_game *game)
{
	hud_map(game);
	hud_cross(game);
	weapon_animate(game, &game->player);
	weapon_draw(game);
}

void	hud_map(t_game *game)
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
			game_draw_rect(game, game->sdl.text_buf, x * 4, y * 4, 4, 4, (game->map.wall[x + (y * game->map.lx)] ? mur : sol));
			y++;
		}
		x++;
	}
	game_draw_rect(game, game->sdl.text_buf, game->player.pos.x * 4, game->player.pos.y * 4, 2 , 2, perso);
	game_draw_rect(game, game->sdl.text_buf, game->player.pos.x * 4 + (game->player.dir.x * 4), game->player.pos.y * 4 + (game->player.dir.y * 4), 2 , 2, face);
}
