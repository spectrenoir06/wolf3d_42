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

#ifndef __APPLE__
	#include "SDL2/SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

#include "wolf3d.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

struct timeval tv1, tv2;

void	game_init_sdl(t_game *game)
{
	game->sdl.lx = WIN_X;
	game->sdl.ly = WIN_Y;
	SDL_CreateWindowAndRenderer(game->sdl.lx,
			game->sdl.ly,
			SDL_WINDOW_SHOWN,
			&game->sdl.win,
			&game->sdl.rd);
	game->sdl.tex = SDL_CreateTexture(game->sdl.rd,
			SDL_PIXELFORMAT_BGRA8888,
			SDL_TEXTUREACCESS_STREAMING,
			game->sdl.lx,
			game->sdl.ly);
	if (game->sdl.win == NULL)
	{
		printf("Wolf3D: Error windows can't load\n");
		exit(1);
	}
	game->sdl.text_buf = malloc(sizeof(Uint32) * game->sdl.lx * game->sdl.ly);
	if (game->sdl.text_buf == NULL)
	{
		printf("Wolf3D: Error can't allocate buffer\n");
		exit(1);
	}
}

void	game_init_map(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	y = 0;

	game->map.color_mur1.a = 255;
	game->map.color_mur1.r = 255;
	game->map.color_mur1.g = 0;
	game->map.color_mur1.b = 0;

	game->map.color_mur2.a = 255;
	game->map.color_mur2.r = 0;
	game->map.color_mur2.g = 0;
	game->map.color_mur2.b = 255;

	game->map.color_ceil.a = 255;
	game->map.color_ceil.r = 180;
	game->map.color_ceil.g = 100;
	game->map.color_ceil.b = 255;

	game->map.color_floor.a = 255;
	game->map.color_floor.r = 100;
	game->map.color_floor.g = 000;
	game->map.color_floor.b = 255;

	game->map.lx = 30;
	game->map.ly = 30;
	game->map.data = (Uint8*)malloc(sizeof(Uint8) * game->map.lx * game->map.ly);
	while (x < game->map.lx)
	{
		y = 0;
		while (y < game->map.ly)
		{
			if (x == 0 || x == game->map.lx - 1 || y == 0 || y == game->map.ly - 1 || rand()%100 > 80)
				game->map.data[x + (y * game->map.lx)] = 1;
			else
				game->map.data[x + (y * game->map.lx)] = 0;
			y++;
		}
		x++;
	}

	game->player.pos.x = 5;
	game->player.pos.y = 5;
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0.66;
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
	color1.r = 100;
	color1.g = 000;
	color1.b = 255;


	color2.a = 255;
	color2.r = 255;
	color2.g = 100;
	color2.b = 000;

	while (x < 30)
	{
		y = 0;
		while (y < 30)
		{
			//game_draw_pixel(game, x, y , color);
			draw_rect(game, x * 4, y * 4, 4, 4, (game->map.data[x + (y * game->map.lx)] ? color1 : color2));
			y++;
		}
		x++;
	}
}

int		main(void)
{

	SDL_Event	event;
	t_game		game;
	t_color		color = {0xFF,0xFF,0xFF,0xFF};
	t_color		color2 = {0xFF,0x00,0x00,0xFF};

	game.player.pos.x = 10;
	game.player.pos.y = 10;

	game.player.dir.x = 0;
	game.player.dir.y = 0;

	double dt = 0;

	SDL_Init(SDL_INIT_VIDEO);
	game_init_sdl(&game);
	game_init_map(&game);
	game_render(&game);
	game_draw_map(&game);
	draw_rect(&game, game.player.pos.x * 4, game.player.pos.y * 4, 2 , 2, color);
	draw_rect(&game, game.player.pos.x * 4 + (game.player.dir.x * 4), game.player.pos.y * 4 + (game.player.dir.y * 4), 2 , 2, color2);
	game_draw_all(&game);
	while (42)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN)
		{
			game_key_down(&game, &event);
			game_render(&game);
			game_draw_map(&game);
			draw_rect(&game, game.player.pos.x * 4, game.player.pos.y * 4, 2 , 2, color);
			draw_rect(&game, game.player.pos.x * 4 + (game.player.dir.x * 4), game.player.pos.y * 4 + (game.player.dir.y * 4), 2 , 2, color2);
			game_draw_all(&game);
		}
		tv2 = tv1;
		gettimeofday(&tv1, NULL);
		dt = ((tv1.tv_sec - tv2.tv_sec) + ((tv1.tv_usec - tv2.tv_usec) / 1000000.0)); //frametime is the time this frame has taken, in seconds
		printf("%f , dt = %f\n",1 / dt, dt); //FPS counter
	}
	return (0);
}

void	game_render(t_game *game)
{
	int	x = 0;

	for(x = 0; x < game->sdl.lx; x++)
	{
		//calculate ray position and direction
		double cameraX = 2.0 * x / (float)game->sdl.lx - 1; //x-coordinate in camera space
		double rayPosX = game->player.pos.x;
		double rayPosY = game->player.pos.y;
		double rayDirX = game->player.dir.x + game->player.plane.x * cameraX;
		double rayDirY = game->player.dir.y + game->player.plane.y * cameraX;
		//which box of the map we're in
		int mapX = (int)rayPosX;
		int mapY = (int)rayPosY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
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
			//Check if ray has hit a wall
			if (game->map.data[mapX + (mapY * game->map.lx)] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
		else
			perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

		//Calculate height of line to draw on screen
		int lineHeight = abs(game->sdl.ly / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game->sdl.ly / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + game->sdl.ly / 2;
		if(drawEnd >= game->sdl.ly)drawEnd = game->sdl.ly - 1;

		//draw the pixels of the stripe as a vertical line
		int y = 0;
		while (y < drawStart)
		{
			game_draw_pixel(game,x,y, game->map.color_ceil);
			y++;
		}
		y = drawStart;
		while (y < drawEnd)
		{
			game_draw_pixel(game,x,y,side ? game->map.color_mur1 : game->map.color_mur2);
			y++;
		}

		while (y < game->sdl.ly)
		{
			game_draw_pixel(game,x,y, game->map.color_floor);
			y++;
		}
	}
}

		void	game_key_down(t_game *game, SDL_Event *event)
		{
			if (event->key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_DestroyWindow(game->sdl.win);
				SDL_Quit();
				exit(0);
			}
			if (event->key.keysym.sym == SDLK_UP)
				game->player.pos.x += game->player.dir.x * 0.1,
				game->player.pos.y += game->player.dir.y * 0.1;
			if (event->key.keysym.sym == SDLK_DOWN)
				game->player.pos.x -= game->player.dir.x * 0.1,
				game->player.pos.y -= game->player.dir.y * 0.1;
			if (event->key.keysym.sym == SDLK_RIGHT)
			{
				double oldDirX = game->player.dir.x;
				game->player.dir.x = game->player.dir.x * cos(-0.02) - game->player.dir.y * sin(-0.02);
				game->player.dir.y = oldDirX * sin(-0.02) + game->player.dir.y * cos(-0.02);
				double oldPlaneX = game->player.plane.x;
				game->player.plane.x = game->player.plane.x * cos(-0.02) - game->player.plane.y * sin(-0.02);
				game->player.plane.y = oldPlaneX * sin(-0.02) + game->player.plane.y * cos(-0.02);
			}
			if (event->key.keysym.sym == SDLK_LEFT)
			{
				double oldDirX = game->player.dir.x;
				game->player.dir.x = game->player.dir.x * cos(0.02) - game->player.dir.y * sin(0.02);
				game->player.dir.y = oldDirX * sin(0.02) + game->player.dir.y * cos(0.02);
				double oldPlaneX = game->player.plane.x;
				game->player.plane.x = game->player.plane.x * cos(0.02) - game->player.plane.y * sin(0.02);
				game->player.plane.y = oldPlaneX * sin(0.02) + game->player.plane.y * cos(0.02);
			}

			//printf("%f, %f \n",game->player.pos.x, game->player.pos.y);
		}

		void	game_draw_all(t_game *game)
		{
			SDL_UpdateTexture(game->sdl.tex, NULL, game->sdl.text_buf, game->sdl.lx * sizeof(Uint32));
			SDL_RenderCopy(game->sdl.rd, game->sdl.tex, NULL, NULL);
			SDL_RenderPresent(game->sdl.rd);
			//bzero(game->sdl.text_buf, sizeof(Uint32) * game->sdl.lx * game->sdl.ly);
		}

		void	game_draw_pixel(t_game *game, int x, int y, t_color c)
		{
			if (x >= 0 && x < game->sdl.lx && y >=0 && y < game->sdl.ly)
				memcpy(&game->sdl.text_buf[x + (y * game->sdl.lx)], &c, 4);
		}

		/*void	game_draw_text(t_game *game)
		{

		}*/
