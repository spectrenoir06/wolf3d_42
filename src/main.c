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
	game->map = (Uint8*)malloc(sizeof(Uint8) * 30 * 30);
	while (x < 30)
	{
		y = 0;
		while (y < 30)
		{
			if (x == 0 || x == 29 || y == 0 || y == 29 || rand()%100 > 80)
				game->map[x + (y * 30)] = 1;
			else
				game->map[x + (y * 30)] = 0;
			y++;
		}
		x++;
	}

	game->map[1 * 12] = 1;

	game->player.x = 5;
	game->player.y = 5;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0.66;
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

	color1.a = 30;
	color1.r = 000;
	color1.g = 000;
	color1.b = 255;


	color2.a = 30;
	color2.r = 255;
	color2.g = 000;
	color2.b = 000;

	while (x < 30)
	{
		y = 0;
		while (y < 30)
		{
			//game_draw_pixel(game, x, y , color);
			draw_rect(game, x * 4, y * 4, 4, 4, (game->map[x + (y * 30)] ? color1 : color2));
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

	game.x = 10;
	game.y = 10;

	game.dx = 0;
	game.dy = 0;

	SDL_Init(SDL_INIT_VIDEO);
	game_init_sdl(&game);
	game_init_map(&game);
	game_render(&game);
	game_draw_map(&game);
	draw_rect(&game, game.player.x * 4, game.player.y * 4, 2 , 2, color);
	draw_rect(&game, game.player.x * 4 + (game.player.dir_x * 4), game.player.y * 4 + (game.player.dir_y * 4), 2 , 2, color2);
	game_draw_all(&game);
	while (42)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN)
		{
			game_key_down(&game, &event);
			game_render(&game);
			game_draw_map(&game);
			draw_rect(&game, game.player.x * 4, game.player.y * 4, 2 , 2, color);
			draw_rect(&game, game.player.x * 4 + (game.player.dir_x * 4), game.player.y * 4 + (game.player.dir_y * 4), 2 , 2, color2);
			game_draw_all(&game);
		}
	}
	return (0);
}

void	game_render(t_game *game)
{
	int	x = 0;
	//int	y = 0;

	t_color		color2;

	color2.a = 255;
	color2.r = 255;
	color2.g = 0;
	color2.b = 0;

	t_color		color1;

	color1.a = 255;
	color1.r = 0;
	color1.g = 255;
	color1.b = 255;
	for(x = 0; x < game->win_lx; x++)
	{
		//calculate ray position and direction
		double cameraX = 2.0 * x / (float)game->win_lx - 1; //x-coordinate in camera space
		double rayPosX = game->player.x;
		double rayPosY = game->player.y;
		double rayDirX = game->player.dir_x + game->plane_x * cameraX;
		double rayDirY = game->player.dir_y + game->plane_y * cameraX;
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
			if (game->map[mapX + (mapY * 30)] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
		else
			perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

		//Calculate height of line to draw on screen
		int lineHeight = abs(game->win_ly / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game->win_ly / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + game->win_ly / 2;
		if(drawEnd >= game->win_ly)drawEnd = game->win_ly - 1;

		//draw the pixels of the stripe as a vertical line
		int y = drawStart;
		while (y < drawEnd)
		{
			game_draw_pixel(game,x,y,side ? color1 : color2);
			y++;
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
			if (event->key.keysym.sym == SDLK_UP)
				game->player.x += game->player.dir_x * 0.1,
				game->player.y += game->player.dir_y * 0.1;
			if (event->key.keysym.sym == SDLK_DOWN)
				game->player.x -= game->player.dir_x * 0.1,
				game->player.y -= game->player.dir_y * 0.1;
			if (event->key.keysym.sym == SDLK_RIGHT)
			{
				double oldDirX = game->player.dir_x;
				game->player.dir_x = game->player.dir_x * cos(-0.02) - game->player.dir_y * sin(-0.02);
				game->player.dir_y = oldDirX * sin(-0.02) + game->player.dir_y * cos(-0.02);
				double oldPlaneX = game->plane_x;
				game->plane_x = game->plane_x * cos(-0.02) - game->plane_y * sin(-0.02);
				game->plane_y = oldPlaneX * sin(-0.02) + game->plane_y * cos(-0.02);
			}
			if (event->key.keysym.sym == SDLK_LEFT)
			{
				double oldDirX = game->player.dir_x;
				game->player.dir_x = game->player.dir_x * cos(0.02) - game->player.dir_y * sin(0.02);
				game->player.dir_y = oldDirX * sin(0.02) + game->player.dir_y * cos(0.02);
				double oldPlaneX = game->plane_x;
				game->plane_x = game->plane_x * cos(0.02) - game->plane_y * sin(0.02);
				game->plane_y = oldPlaneX * sin(0.02) + game->plane_y * cos(0.02);
			}

			//printf("%f, %f \n",game->player.x, game->player.y);
		}

		void	game_draw_all(t_game *game)
		{
			SDL_UpdateTexture(game->tex, NULL, game->text_buf, game->win_lx * sizeof(Uint32));
			SDL_RenderCopy(game->rd, game->tex, NULL, NULL);
			SDL_RenderPresent(game->rd);
			bzero(game->text_buf, sizeof(Uint32) * game->win_lx * game->win_ly);
		}

		void	game_draw_pixel(t_game *game, int x, int y, t_color c)
		{
			if (x >= 0 && x < game->win_lx && y >=0 && y < game->win_ly)
				memcpy(&game->text_buf[x + (y * game->win_lx)], &c, 4);
		}
