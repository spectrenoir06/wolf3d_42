/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
			SDL_PIXELFORMAT_ABGR8888,
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
	if(SDL_NumJoysticks() == 1)
	{
		SDL_JoystickEventState(SDL_ENABLE);
		game->joystick = SDL_JoystickOpen(0);
	}
}

void	game_init_map(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	game->map.textures[2] = SDL_LoadBMP("img/2.bmp");
	game->map.textures[1] = SDL_LoadBMP("img/1.bmp");
	game->map.textures[0] = SDL_LoadBMP("img/2.bmp");

	game->map.color_ceil.a = 255;
	game->map.color_ceil.r = 53;
	game->map.color_ceil.g = 193;
	game->map.color_ceil.b = 206;

	game->map.color_floor.a = 255;
	game->map.color_floor.r = 92;
	game->map.color_floor.g = 167;
	game->map.color_floor.b = 98;

	game->map.lx = 30;
	game->map.ly = 30;
	game->map.data = (Uint8*)malloc(sizeof(Uint8) * game->map.lx * game->map.ly);
	while (x < game->map.lx)
	{
		y = 0;
		while (y < game->map.ly)
		{
			if (x == 0 || x == game->map.lx - 1 || y == 0 || y == game->map.ly - 1 || rand()%100 > 90)
				game->map.data[x + (y * game->map.lx)] = (rand()%100 > 50 ? 1 : 2);
			else
				game->map.data[x + (y * game->map.lx)] = 0;
			y++;
		}
		x++;
	}

	x = 0;

	while (x < 10)
	{
		game->input[x++] = 0;
	}
	game->player.pos.x = 5.3;
	game->player.pos.y = 5.3;
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0.66;
}

void	game_draw_rect(t_game *game, int x, int y, int lx, int ly, t_color c)
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
			game_draw_rect(game, x * 4, y * 4, 4, 4, (game->map.data[x + (y * game->map.lx)] ? color1 : color2));
			y++;
		}
		x++;
	}
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
		memcpy(&game->sdl.text_buf[x + (y * game->sdl.lx)], &c, 3);
}

void	game_render(t_game *game)
{
	int	x = 0;
	int wall_nb;

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
			if (game->map.data[mapX + (mapY * game->map.lx)] > 0)
			{
				wall_nb = game->map.data[mapX + (mapY * game->map.lx)];
				hit = 1;
			}
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
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + game->sdl.ly / 2;
		if(drawEnd >= game->sdl.ly)
			drawEnd = game->sdl.ly - 1;


		double wallX;
		if (side == 1)
			 wallX = rayPosX + ((mapY - rayPosY + (1 - stepY) / 2) / rayDirY) * rayDirX;
		else
			wallX = rayPosY + ((mapX - rayPosX + (1 - stepX) / 2) / rayDirX) * rayDirY;
		wallX -= floor(wallX);

		int texX = wallX * 512;
		if(side == 0 && rayDirX > 0) texX = 512 - texX - 1;
		if(side == 1 && rayDirY < 0) texX = 512 - texX - 1;

		//draw the pixels of the stripe as a vertical line
		int y = 0;
		while (y < drawStart)
		{
			game_draw_pixel(game,x,y, game->map.color_ceil);
			y++;
		}
		y = drawStart;
		while (y <= drawEnd)
		{
			int texY = (y * 2 - game->sdl.ly + lineHeight)* (512/2)/lineHeight;
			//int texY = (y - drawStart) * 512 / (drawEnd - drawStart);
			t_color color;
			color.r = ((Uint8*)(game->map.textures[wall_nb]->pixels))[texX * 3 + (texY * 3 * 512)];
			color.g = ((Uint8*)(game->map.textures[wall_nb]->pixels))[texX * 3 + (texY * 3 * 512) + 1];
			color.b = ((Uint8*)(game->map.textures[wall_nb]->pixels))[texX * 3 + (texY * 3 * 512) + 2];

			if(side == 1)
			{
				color.r = color.r >> 1;
				color.g = color.g >> 1;
				color.b = color.b >> 1;
			}
			game_draw_pixel(game,x,y,color);
			y++;
		}

		while (y < game->sdl.ly)
		{
			game_draw_pixel(game,x,y, game->map.color_floor);
			y++;
		}
	}
}

int		game_event_handler(t_game *game)
{
	 SDL_Event event;

	if (!SDL_PollEvent(&event))
		return (0);
	if (event.type == SDL_MOUSEMOTION)
	{
		game->input[MOUSE_X] = event.motion.xrel;
		game->input[MOUSE_Y] = event.motion.yrel;
		return (1);
	}
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z)
			game->input[UP] = 1;
		else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
			game->input[DOWN] = 1;
		else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q)
			game->input[LEFT] = 1;
		else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
			game->input[RIGHT] = 1;
		else if (event.key.keysym.sym == SDLK_a)
			game->input[TURN_LEFT] = 1;
		else if (event.key.keysym.sym == SDLK_e)
			game->input[TURN_RIGHT] = 1;
		else if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_JoystickClose(0);
			SDL_DestroyWindow(game->sdl.win);
			SDL_Quit();
			exit(0);
		}
		return (1);
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z)
			game->input[UP] = 0;
		else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
			game->input[DOWN] = 0;
		else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q)
			game->input[LEFT] = 0;
		else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
			game->input[RIGHT] = 0;
		else if (event.key.keysym.sym == SDLK_a)
			game->input[TURN_LEFT] = 0;
		else if (event.key.keysym.sym == SDLK_e)
			game->input[TURN_RIGHT] = 0;
	}
	else if(event.type == SDL_JOYBUTTONDOWN)
	{
		//printf("Button = %d\n", event.jbutton.button);
		if (event.jbutton.button == 11)
			game->input[UP] = SINT16_MAX;
		else if (event.jbutton.button == 12)
			game->input[DOWN] = 1;
		else if (event.jbutton.button == 13)
			game->input[LEFT] = 1;
		else if (event.jbutton.button == 14)
			game->input[RIGHT] = 1;
		else if (event.jbutton.button == 4)
			game->input[TURN_LEFT] = 1;
		else if (event.jbutton.button == 5)
			game->input[TURN_RIGHT] = 1;
		else if (event.jbutton.button == 10)
		{
			SDL_JoystickClose(0);
			SDL_DestroyWindow(game->sdl.win);
			SDL_Quit();
			exit(0);
		}
	}
	else if(event.type == SDL_JOYBUTTONUP)
	{
		//printf("R-Button = %d\n", event.jbutton.button);
		if (event.jbutton.button == 11)
			game->input[UP] = 0;
		else if (event.jbutton.button == 12)
			game->input[DOWN] = 0;
		else if (event.jbutton.button == 13)
			game->input[LEFT] = 0;
		else if (event.jbutton.button == 14)
			game->input[RIGHT] = 0;
		else if (event.jbutton.button == 4)
			game->input[TURN_LEFT] = 0;
		else if (event.jbutton.button == 5)
			game->input[TURN_RIGHT] = 0;
	}
	else if (event.type == SDL_JOYAXISMOTION)
	{
		double test;
		if (event.jaxis.axis == 1 && (event.jaxis.value > 3000 || event.jaxis.value < -3000))
			game->input[UP] = event.jaxis.value;
		else if (event.jaxis.axis == 1)
			game->input[UP] = 0;
		if (event.jaxis.axis == 0 && (event.jaxis.value > 3000 || event.jaxis.value < -3000))
			game->input[LEFT] = event.jaxis.value;
		else if (event.jaxis.axis == 0)
			game->input[LEFT] = 0;
	}
	else if (event.type == SDL_QUIT)
	{
		SDL_JoystickClose(0);
		SDL_DestroyWindow(game->sdl.win);
		SDL_Quit();
		exit(0);
	}
	return (1);
}
