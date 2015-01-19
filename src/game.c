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

typedef	struct	s_ray
{
	t_vect2dd	pos;
	t_vect2dd	dir;
	t_vect2dd	delta;
	t_vect2dd	side;
}				t_ray;

void	game_init_sdl(t_game *game)
{
	game->sdl.lx = WIN_X;
	game->sdl.ly = WIN_Y;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		exit(EXIT_FAILURE);

	SDL_CreateWindowAndRenderer(game->sdl.lx,
			game->sdl.ly,
			SDL_WINDOW_SHOWN,
			&(game->sdl.win),
			&(game->sdl.rd));
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
	SDL_SetRelativeMouseMode(1);
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
void	init_ray(t_game *game, t_ray *ray, double camera_x)
{
	ray->pos.x = game->player.pos.x;
	ray->pos.y = game->player.pos.y;

	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;

	ray->delta.x = sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	ray->delta.y = sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
}

void	ray_caster(t_game *game, t_ray *ray)
{

}

void	game_render(t_game *game)
{
	int	x = 0;
	int wall_nb;

	for(x = 0; x < game->sdl.lx; x++)
	{
		//calculate ray position and direction
		t_ray ray;

		double camera_x = 2.0 * x / (float)game->sdl.lx - 1; //x-coordinate in camera space
		init_ray(game, &ray, camera_x);



		int mapX = (int)ray.pos.x;
		int mapY = (int)ray.pos.y;

		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (ray.dir.x < 0)
		{
			stepX = -1;
			ray.side.x = (ray.pos.x - mapX) * ray.delta.x;
		}
		else
		{
			stepX = 1;
			ray.side.x = (mapX + 1.0 - ray.pos.x) * ray.delta.x;
		}
		if (ray.dir.y < 0)
		{
			stepY = -1;
			ray.side.y = (ray.pos.y - mapY) * ray.delta.y;
		}
		else
		{
			stepY = 1;
			ray.side.y = (mapY + 1.0 - ray.pos.y) * ray.delta.y;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (ray.side.x < ray.side.y)
			{
				ray.side.x += ray.delta.x;
				mapX += stepX;
				side = 0;
			}
			else
			{
				ray.side.y += ray.delta.y;
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
			perpWallDist = fabs((mapX - ray.pos.x + (1 - stepX) / 2) / ray.dir.x);
		else
			perpWallDist = fabs((mapY - ray.pos.y + (1 - stepY) / 2) / ray.dir.y);

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
			 wallX = ray.pos.x + ((mapY - ray.pos.y + (1 - stepY) / 2) / ray.dir.y) * ray.dir.x;
		else
			wallX = ray.pos.y + ((mapX - ray.pos.x + (1 - stepX) / 2) / ray.dir.x) * ray.dir.y;
		wallX -= floor(wallX);

		int texX = wallX * 512;
		if(side == 0 && ray.dir.x > 0) texX = 512 - texX - 1;
		if(side == 1 && ray.dir.y < 0) texX = 512 - texX - 1;

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
//	if (event.type == SDL_MOUSEMOTION)
//	{
//		printf("Mouse %d\n", event.motion.xrel * 1000);
//		if (event.motion.xrel * 1000 > SINT16_MIN && event.motion.xrel * 1000 < SINT16_MAX)
//			game->input[ROT_Z] = event.motion.xrel * 1000;
//		//game->input[ROT_Y] = event.motion.yrel *1000;
//		return (1);
//	}
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
			game->input[MOV_Y] = SINT16_MAX;
		else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
			game->input[MOV_Y] = SINT16_MIN;
		else if (event.key.keysym.sym == SDLK_a)
			game->input[MOV_X] = SINT16_MIN;
		else if (event.key.keysym.sym == SDLK_d)
			game->input[MOV_X] = SINT16_MAX;
		else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q)
			game->input[ROT_Z] = SINT16_MIN;
		else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_e)
			game->input[ROT_Z] = SINT16_MAX;
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
		if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
			game->input[MOV_Y] = 0;
		else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
			game->input[MOV_Y] = 0;
		else if (event.key.keysym.sym == SDLK_a)
			game->input[MOV_X] = 0;
		else if (event.key.keysym.sym == SDLK_d)
			game->input[MOV_X] = 0;
		else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q)
			game->input[ROT_Z] = 0;
		else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_e)
			game->input[ROT_Z] = 0;
	}
	else if(event.type == SDL_JOYBUTTONDOWN)
	{
		printf("Button = %d\n", event.jbutton.button);
		if (event.jbutton.button == 11)
			game->input[MOV_Y] = SINT16_MAX;
		else if (event.jbutton.button == 12)
			game->input[MOV_Y] = SINT16_MIN;
		else if (event.jbutton.button == 13)
			game->input[MOV_X] = SINT16_MIN;
		else if (event.jbutton.button == 14)
			game->input[MOV_X] = SINT16_MAX;
		else if (event.jbutton.button == 4)
			game->input[ROT_Z] = SINT16_MIN;
		else if (event.jbutton.button == 5)
			game->input[ROT_Z] = SINT16_MAX;
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
		if (event.jbutton.button == 11 || event.jbutton.button == 12)
			game->input[MOV_Y] = 0;
		else if (event.jbutton.button == 13 || event.jbutton.button == 14)
			game->input[MOV_X] = 0;
		else if (event.jbutton.button == 4 || event.jbutton.button == 5)
			game->input[ROT_Z] = 0;
	}
	else if (event.type == SDL_JOYAXISMOTION)
	{
		double test;
		if (event.jaxis.axis == 1 && (event.jaxis.value > 5000 || event.jaxis.value < -5000))
			game->input[MOV_Y] = -event.jaxis.value;
		else if (event.jaxis.axis == 1)
			game->input[MOV_Y] = 0;
		if (event.jaxis.axis == 0 && (event.jaxis.value > 5000 || event.jaxis.value < -5000))
			game->input[MOV_X] = event.jaxis.value;
		else if (event.jaxis.axis == 0)
			game->input[MOV_X] = 0;
		if (event.jaxis.axis == 3 && (event.jaxis.value > 5000 || event.jaxis.value < -5000))
			game->input[ROT_Z] = event.jaxis.value;
		else if (event.jaxis.axis == 3)
			game->input[ROT_Z] = 0;

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
