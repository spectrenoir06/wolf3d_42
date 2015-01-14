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
	game->player.x = 2;
	game->player.y = 2;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
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
	//t_color		color;

	/*color.a = 255;
	color.r = 255;
	color.g = 255;
	color.b = 255;*/

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
		game_render(&game);
		game_draw_all(&game);
	}
	return (0);
}

void	game_render(t_game *game)
{
	int	x = 0;
	int	y = 0;

	t_color		color;

	color.a = 255;
	color.r = 0;
	color.g = 255;
	color.b = 255;

	t_color		color1;

	color1.a = 255;
	color1.r = 0;
	color1.g = 255;
	color1.b = 255;

	while (x < game->win_lx)
	{
		double cameraX = (x / (float)game->win_lx - 1);
		double rayPosX = game->player.x;
		double rayPosY = game->player.y;
		double rayDirX = game->player.dir_x + game->plane_x * cameraX;
		double rayDirY = game->player.dir_y + game->plane_y * cameraX;

		int mapX = (int)rayPosX;
		int mapY = (int)rayPosY;

		double deltaDistX = sqrt(1 + (rayDirY * rayDirY ) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

		double sideDistX;
		double sideDistY;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		double perpWallDist;

		if (rayDirX<0){
			stepX=-1;// vecteur de direction
			sideDistX = (rayPosX - mapX) * deltaDistX;// distance
		} else{
			stepX = 1;
		 	sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0){
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		} else{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}

		while (!hit)
		{
			if (sideDistX<sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->map[mapX + (mapY * 10)] > 0)
			{
				hit=1;
			}
			if (side == 0)
			{
				perpWallDist = abs((mapX-rayPosX+(1-stepX)/2)/rayDirX);
			}
			else
			{
				perpWallDist = abs((mapY-rayPosY+(1-stepY)/2)/rayDirY);
			}
		}

		int hauteurLigne = abs(game->win_ly / perpWallDist);

		int drawStart = (-hauteurLigne / 2.0 + game->win_ly / 2.0);
		int drawEnd = (hauteurLigne / 2 + game->win_ly / 2.0);

		if (drawStart < 0) {
			drawStart = 0;
		}
		if (drawEnd >= game->win_ly) {
			drawEnd = game->win_ly - 1;
		}

		y = 0;
		while (y < drawEnd)
		{
			game_draw_pixel(game, x, y, side ? color : color1);
			y++;
		}
		x++;
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
	if (x >= 0 && x < game->win_lx && y >=0 && y < game->win_ly)
		memcpy(&game->text_buf[x + (y * game->win_lx)], &c, 4);
}
