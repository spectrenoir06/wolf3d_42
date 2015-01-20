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

typedef struct s_wall
{
	t_vect2di	map;
	double		dist;
	int			side;
	int			id;
	t_vect2di	step;
}				t_wall;

void	game_init_sdl(t_game *game)
{
	game->sdl.lx = WIN_X;
	game->sdl.ly = WIN_Y;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) < 0)
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
		game->haptic = SDL_HapticOpenFromJoystick(game->joystick);
		if (SDL_HapticRumbleInit(game->haptic))
				printf("Can not init %s\n", SDL_GetError());
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

t_wall	ray_caster(t_game *game, t_ray *ray, t_wall *wall)
{
	wall->map.x = (int)ray->pos.x;
	wall->map.y = (int)ray->pos.y;

	int hit = 0;

	if (ray->dir.x < 0)
	{
		wall->step.x = -1;
		ray->side.x = (ray->pos.x - wall->map.x) * ray->delta.x;
	}
	else
	{
		wall->step.x = 1;
		ray->side.x = (wall->map.x + 1.0 - ray->pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		wall->step.y = -1;
		ray->side.y = (ray->pos.y - wall->map.y) * ray->delta.y;
	}
	else
	{
		wall->step.y = 1;
		ray->side.y = (wall->map.y + 1.0 - ray->pos.y) * ray->delta.y;
	}

	while (hit == 0)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			wall->map.x += wall->step.x;
			wall->side = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			wall->map.y += wall->step.y;
			wall->side = 1;
		}

		if (game->map.data[wall->map.x + (wall->map.y * game->map.lx)] > 0)
		{
			wall->id = game->map.data[wall->map.x + (wall->map.y * game->map.lx)];
			hit = 1;
		}
	}

	if (wall->side == 0)
		wall->dist = fabs((wall->map.x - ray->pos.x + (1 - wall->step.x) / 2) / ray->dir.x);
	else
		wall->dist = fabs((wall->map.y - ray->pos.y + (1 - wall->step.y) / 2) / ray->dir.y);
}

void	draw_ceil(t_game *game,int x, int end)
{
	int y = 0;
	while (y < end)
	{
		game_draw_pixel(game,x,y, game->map.color_ceil);
		y++;
	}
}

void	draw_floor(t_game *game,int x, int y)
{
	while (y < game->sdl.ly)
	{
		game_draw_pixel(game,x,y, game->map.color_floor);
		y++;
	}
}

void	game_render(t_game *game)
{
	int	x = 0;

	for(x = 0; x < game->sdl.lx; x++)
	{
		//calculate ray position and direction
		t_ray ray;
		t_wall wall;

		double camera_x = 2.0 * x / (float)game->sdl.lx - 1; //x-coordinate in camera space

		init_ray(game, &ray, camera_x);
		ray_caster(game, &ray, &wall);

		int lineHeight = abs(game->sdl.ly / wall.dist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game->sdl.ly / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + game->sdl.ly / 2;
		if(drawEnd >= game->sdl.ly)
			drawEnd = game->sdl.ly - 1;


		double wallX;
		if (wall.side == 1)
			 wallX = ray.pos.x + ((wall.map.y - ray.pos.y + (1 - wall.step.y) / 2) / ray.dir.y) * ray.dir.x;
		else
			wallX = ray.pos.y + ((wall.map.x - ray.pos.x + (1 - wall.step.x) / 2) / ray.dir.x) * ray.dir.y;
		wallX -= floor(wallX);

		int texX = 512 - wallX * 512;
		if(wall.side == 0 && ray.dir.x > 0) texX = 512 - texX - 1;
		if(wall.side == 1 && ray.dir.y < 0) texX = 512 - texX - 1;

		draw_ceil(game, game->sdl.lx - x, drawStart);

		int y = drawStart;

		while (y < drawEnd)
		{
			int texY = (y * 2 - game->sdl.ly + lineHeight)* (512/2)/lineHeight;
			//int texY = (y - drawStart) * 512 / (drawEnd - drawStart);
			t_color color;
			color.r = ((Uint8*)(game->map.textures[wall.id]->pixels))[texX * 3 + (texY * 3 * 512)];
			color.g = ((Uint8*)(game->map.textures[wall.id]->pixels))[texX * 3 + (texY * 3 * 512) + 1];
			color.b = ((Uint8*)(game->map.textures[wall.id]->pixels))[texX * 3 + (texY * 3 * 512) + 2];
			if(wall.side == 1)
			{
				color.r = color.r >> 1;
				color.g = color.g >> 1;
				color.b = color.b >> 1;
			}
			game_draw_pixel(game, game->sdl.lx - x, y, color);
			y++;
		}
		//draw_floor(game, game->sdl.lx - x, y);

		// positions X et Y du texel du sol au bas du mur
		double floorXWall;
		double floorYWall;

		double weight;// coefficient de ponderation
		double currentFloorX;// position du pixel sur X
		double currentFloorY;// position du pixel sur Y
		double floorTexX;// position du texel sur X
		double floorTexY;// position du texel sur Y
		double distWall = wall.dist;// distance du mur
		double distPlayer = 0;// distance de la camera
		double currentDist = 0;// point de depart de la texture
		int h = game->sdl.ly;

		if (wall.side == 0 && ray.dir.x > 0) {
			// nord
			floorXWall = wall.map.x;
			floorYWall = wall.map.y + wallX;
		} else if (wall.side == 0 && ray.dir.x < 0) {
			// sud
			floorXWall = wall.map.x + 1.0;
			floorYWall = wall.map.y + wallX;
		} else if (wall.side == 1 && ray.dir.y > 0) {
			// est
			floorXWall = wall.map.x + wallX;
			floorYWall = wall.map.y;
		} else {
			// ouest
			floorXWall = wall.map.x + wallX;
			floorYWall = wall.map.y + 1.0;
		}

		//trace le sol de drawEnd au bas de l'ecran
		y=drawEnd;
		while (y < h) {

			currentDist = h / (2 * y - h);// distance
			weight = (currentDist - distPlayer) / (distWall - distPlayer);// coef
			currentFloorX = weight * floorXWall + (1.0 - weight) * x;// position sur X
			currentFloorY = weight * floorYWall + (1.0 - weight) * y;// position sur Y
			floorTexX = (int)(currentFloorX * 512.0) % 512;// position texel sur X
			floorTexY = (int)(currentFloorY * 512.0) % 512;// position texel sur Y

			t_color color;

			color.r = ((Uint8*)(game->map.textures[1]->pixels))[(int)floorTexX * 3 + ((int)floorTexY * 3 * 512)];
			color.g = ((Uint8*)(game->map.textures[1]->pixels))[(int)floorTexX * 3 + ((int)floorTexY * 3 * 512) + 1];
			color.b = ((Uint8*)(game->map.textures[1]->pixels))[(int)floorTexX * 3 + ((int)floorTexY * 3 * 512) + 2];

			game_draw_pixel(game, x, y, color);// trace le sol
			//game_draw_pixel(game, x, h - y - 1, game->map.textures[2][floorTexX][floorTexY]);// trace le plafond
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
		//printf("Mouse %d\n", event.motion.xrel);
		if (event.motion.xrel > SINT16_MIN && event.motion.xrel < SINT16_MAX)
			game->input[ROT_Z_M] = event.motion.xrel;
		//game->input[ROT_Y] = event.motion.yrel *1000;
		return (1);
	}
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
		else if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
			game->player.speed += 3;
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
		else if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
			game->player.speed -= 3;
	}
	else if(event.type == SDL_JOYBUTTONDOWN)
	{
		//printf("Button = %d\n", event.jbutton.button);
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
		else if (event.jbutton.button == 6)
			game->player.speed += 3;
		//else if (event.jbutton.button == 0)
		//	SDL_HapticRumblePlay(game->haptic, 0.8, SDL_HAPTIC_INFINITY);
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
		//else if (event.jbutton.button == 0)
		//	SDL_HapticRumbleStop(game->haptic);
		else if (event.jbutton.button == 6)
			game->player.speed -= 3;
	}
	else if (event.type == SDL_JOYAXISMOTION)
	{
		double test;
		if (event.jaxis.axis == 1 && (event.jaxis.value > 5000 || event.jaxis.value < -5000))
			game->input[MOV_Y] = event.jaxis.value;
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
