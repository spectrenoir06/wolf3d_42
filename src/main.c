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

#include "SDL.h"
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
									SDL_PIXELFORMAT_BGRA8888,
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

void	game_init_map(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	game->map = (Uint8*)malloc(sizeof(Uint8) * 100);
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			if (x == 0 || x == 9 || y == 0 || y == 9)
				game->map[x + (y * 10)] = 1;
			else
				game->map[x + (y * 10)] = 0;
			y++;
		}
		x++;
	}
	game->player.x = 200;
	game->player.y = 200;
	game->player.dir_x = 0;
	game->player.dir_y = 1;
}

void	draw_rect(t_game *game, int x, int y, int lx, int ly, t_color c)
{
	int a = x;
	int b = y;

	while (a < (x + lx))
	{
		b = y;
		while (b < (y + ly))
		{
			game_draw_pixel(game, a, b , c);
			b++;
		}
		a++;
	}
}

void	game_draw_map(t_game *game)
{
	int x = 0;
	int y = 0;

	t_color		color1;
	t_color		color2;

	color1.a = 255;
	color1.r = 000;
	color1.g = 000;
	color1.b = 255;


	color2.a = 255;
	color2.r = 255;
	color2.g = 000;
	color2.b = 000;

	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			//game_draw_pixel(game, x, y , color);
			draw_rect(game, x * 100, y * 100, 100, 100, (game->map[x + (y * 10)] ? color1 : color2));
			y++;
		}
		x++;
	}
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
	game_init_map(&game);

	while (42)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN)
			game_key_down(&game, &event);



		//game_draw_map(&game);
		//draw_rect(&game, game.player.x, game.player.y, 50 , 50, color);
		game_draw_all(&game);
	}
	return (0);
}

void	game_render(t_game *game)
{
	int x = 0;
	int y = 0;

	int camera_x = (2 * x / game->win_lx)-1;
	int ray_pos_x = game->player.x;
	int ray_pos_y = game->player.y;
	int ray_dir_x = game->player.dir_x * camera_x;
	int ray_dir_y = game->player.dir_y * camera_x;

	int mapx = game->player.x / 100;
	int mapy = game->player.x / 100;

	int sideDistX;
	int sideDistY;

	int deltaDistX = sqrt(1+(ray_dir_y * ray_dir_y)/(ray_dir_x * ray_dir_x));
	int deltaDistY = sqrt(1+(ray_dir_x * ray_dir_x)/(ray_dir_y * ray_dir_y));

	int stepX;
	int stepY;

	int hit = 0;
	int side;

	while (x <= game->win_lx)
	{

		if (ray_dir_x<0){
			stepX=-1;// vecteur de direction
			sideDistX = (ray_pos_x - mapx) * deltaDistX;// distance
		} else{
			stepX = 1;
			sideDistX = (mapx + 1.0 - ray_pos_x) * deltaDistX;
		}
		if (ray_dir_y < 0){
			stepY = -1;
			sideDistY = (ray_pos_y - mapy) * deltaDistY;
		} else{
			stepY = 1;
			sideDistY = (mapy + 1.0 - ray_pos_y) * deltaDistY;
		}

		while (hit == 0) {

			//Passe  la case suivante sur X ou Y
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;// agrandis le rayon
				mapx += stepX;// prochaine case ou case prcdente sur X
				side = 0;// orientation du mur
			} else {
				sideDistY += deltaDistY;// agrandis le rayon
				mapy += stepY;// prochaine case ou case prcdente sur Y
				side = 1;// orientation du mur
			}

			// si le rayon rencontre un mur
			if (game->map[x + (y * 10)]>0) {
				hit=1;// stoppe la boucle
			}
	}
}
}

void	game_key_down(t_game *game, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(game->win);
		SDL_Quit();
		exit(0);
	}
	if (event->key.keysym.sym == SDLK_w)
		game->player.y--;
	if (event->key.keysym.sym == SDLK_s)
		game->player.y++;
	if (event->key.keysym.sym == SDLK_a)
		game->player.x--;
	if (event->key.keysym.sym == SDLK_d)
		game->player.x++;
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
