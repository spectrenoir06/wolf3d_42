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

#include "SDL2/SDL.h"
#include "wolf3d.h"
#include <stdio.h>

void	game_init_sdl(t_game *game)
{
	game->win_lx = WIN_X;
	game->win_ly = WIN_Y;
	SDL_CreateWindowAndRenderer(game->win_lx,
								game->win_ly,
								SDL_WINDOW_SHOWN,
								&game->win,
								&game->rd);
	game->tex = SDL_CreateTexture(	game->rd,
									SDL_PIXELFORMAT_ARGB8888,
									SDL_TEXTUREACCESS_STREAMING,
									game->win_lx,
									game->win_ly);
	if (game->win == NULL)
	{
		printf("Wolf3D: Error windows can't load\n");
		exit(1);
	}
			game->text_buf = malloc(sizeof(Uint32) * game->win_lx * game->win_ly);
	if (game->text_buf == NULL)
	{
		printf("Wolf3D: Error can't allocate buffer\n");
		exit(1);
	}
	memset(game->text_buf, 0XD0, game->win_lx * game->win_ly * sizeof(Uint32));

}

int		main(void)
{

	SDL_Event	event;
	t_game		game;
	t_color		color;

	color.a = 255;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	game.x = 10;
	game.y = 10;

	game.dx = 0;
	game.dy = 0;

	SDL_Init(SDL_INIT_VIDEO);
	game_init_sdl(&game);

	while (42)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN)
			game_key_down(&game, &event);
		game.x += game.dx;
		game.y += game.dy;
		game_draw_pixel(&game, game.x, game.y, color);
		game_draw_all(&game);
	}
	return (0);
}

void	game_key_down(t_game *game, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(game->win);
		SDL_Quit();
		exit(0);
	}
	else if (event->key.keysym.sym == SDLK_w)
		game->dy = -1, game->dx = 0;
	else if (event->key.keysym.sym == SDLK_s)
		game->dy = 1 , game->dx = 0;
	else if (event->key.keysym.sym == SDLK_a)
		game->dx = -1, game->dy = 0;
	else if (event->key.keysym.sym == SDLK_d)
		game->dx = 1, game->dy = 0;
}

void	game_draw_all(t_game *game)
{
	SDL_UpdateTexture(game->tex, NULL, game->text_buf, game->win_lx * sizeof(Uint32));
	SDL_RenderCopy(game->rd, game->tex, NULL, NULL);
	SDL_RenderPresent(game->rd);
}

void	game_draw_pixel(t_game *game, int x, int y, t_color c)
{
	if (x >= 0
		&& x < game->win_lx
		&& y >=0
		&& y < game->win_ly)
		memcpy(&game->text_buf[x + (y * game->win_lx)], &c, 4);
}
