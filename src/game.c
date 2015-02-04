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
#include <math.h>

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
			SDL_PIXELFORMAT_RGB888,
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

	game_init_sdl_mixer(&game->sounds);
	SDL_SetRelativeMouseMode(1);
}



void	game_draw_rect(t_game *game, Uint32 *buf, int x, int y,int color)
{
	int a = x;
	int b = y;
	t_color	c;

	c.r = color / 0x10000;
	c.g = (color % 0x10000) / 0x100;
	c.b = color % 0x100;
	while (a < (x + 4))
	{
		b = y;
		while (b < (y + 4))
		{
			game_draw_pixel(game, buf, a, b , &c);
			b++;
		}
		a++;
	}
}



void	game_draw_all(t_game *game)
{
	//hud_put(game);
	SDL_UpdateTexture(game->sdl.tex, NULL, game->sdl.text_buf, game->sdl.lx * sizeof(Uint32));
	SDL_RenderCopy(game->sdl.rd, game->sdl.tex, NULL, NULL);
	SDL_RenderPresent(game->sdl.rd);
	//bzero(game->sdl.text_buf, sizeof(Uint32) * game->sdl.lx * game->sdl.ly);
}

inline void	game_draw_pixel(t_game *game, Uint32 *buf, int x, int y, void *c)
{
	//if (x >= 0 && x < game->sdl.lx && y >=0 && y < game->sdl.ly)
		ft_memcpy(&buf[x + (y * game->sdl.lx)], c, 3);
}

inline void	game_draw_pixel_black(t_game *game, Uint32 *buf, int x, int y, void *c)
{
	t_color color;
	ft_memcpy(&color, c, 3);

	color.r = color.r >> 1;
	color.g = color.g >> 1;
	color.b = color.b >> 1;
	//if (x >= 0 && x < game->sdl.lx && y >=0 && y < game->sdl.ly)
		ft_memcpy(&buf[x + (y * game->sdl.lx)], &color, 3);
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

void	ray_caster(t_game *game, t_ray *ray, t_wall *wall)
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

		if (game->map.wall[wall->map.x + (wall->map.y * game->map.lx)] > 0)
		{
			wall->id = game->map.wall[wall->map.x + (wall->map.y * game->map.lx)];
			hit = 1;
		}
	}

	if (wall->side == 0)
		wall->dist = fabs((wall->map.x - ray->pos.x + (1 - wall->step.x) / 2) / ray->dir.x);
	else
		wall->dist = fabs((wall->map.y - ray->pos.y + (1 - wall->step.y) / 2) / ray->dir.y);
}

void	draw_floor_and_ceil(t_game *game, int x, int y, t_ray ray, t_wall *wall, double wallX)
{
	t_vect2dd	floor;
	double		weight;				// coefficient de ponderation
	t_vect2dd	current_floor;
	t_vect2dd	floor_tex;

	if (wall->side == 0 && ray.dir.x > 0)
	{
		floor.x = wall->map.x;
		floor.y = wall->map.y + wallX;
	}
	else if (wall->side == 0 && ray.dir.x < 0)
	{
		floor.x = wall->map.x + 1.0;
		floor.y = wall->map.y + wallX;
	}
	else if (wall->side == 1 && ray.dir.y > 0)
	{
		floor.x = wall->map.x + wallX;
		floor.y = wall->map.y;
	}
	else
	{
		floor.x = wall->map.x + wallX;
		floor.y = wall->map.y + 1.0;
	}

	while (y <= GAME_LY)
	{
		weight = (game->calcule[y - (GAME_LY / 2)]) / (wall->dist);// coef
		current_floor.x = weight * floor.x + (1.0 - weight) * game->player.pos.x;// position sur X
		current_floor.y = weight * floor.y + (1.0 - weight) * game->player.pos.y;// position sur Y
		floor_tex.x = (int)(current_floor.x * TEX_SIZE) % TEX_SIZE;// position texel sur X
		floor_tex.y = (int)(current_floor.y * TEX_SIZE) % TEX_SIZE;// position texel sur Y

		t_color *color;

		Uint8 test = game->map.floor[((int)current_floor.x) + ((int)(current_floor.y) * game->map.lx)];
		Uint8 test2 = game->map.ceil[((int)current_floor.x) + ((int)(current_floor.y) * game->map.lx)];

		color = (void *) &((Uint8*)(game->map.textures[test2]->pixels))[(int)floor_tex.x * 3 + ((int)floor_tex.y * 3 * TEX_SIZE)];

		t_color *color2;

		color2 = (void *) &((Uint8*)(game->map.textures[test]->pixels))[(int)floor_tex.x * 3 + ((int)floor_tex.y * 3 * TEX_SIZE) + 0];

		double	angle = atan2(game->player.dir.y, game->player.dir.x);
		int	sky = x + (angle) / (M_PI ) * (double)(game->map.sky->w );
		sky %= game->map.sky->w;

		if (!(color->r == 0xFF && color->g == 0x00 && color->b == 0xFF))
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, y + GAME_Y, color);						// trace le sol
		else
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, y + GAME_Y, &((Uint8 *)(game->map.sky->pixels))[(sky) * 3 + (y *  (game->map.sky->w) * 3)]);

		if (!(color2->r == 0xFF && color2->g == 0x00 && color2->b == 0xFF))
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, GAME_LY + GAME_Y - y, color2);	// trace le plafond
		else
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, GAME_LY + GAME_Y - y, &((Uint8 *)(game->map.sky->pixels))[(sky) * 3 + (((GAME_LY) - y) * (game->map.sky->w) * 3)]);
		y++;
	}
}

void	game_render(t_game *game)
{
	int	x = 0;

	for(x = 0; x < GAME_LX; x++)
	{
		//calculate ray position and direction
		t_ray ray;
		t_wall wall;

		double camera_x = 2.0 * x / (float)GAME_LX - 1; //x-coordinate in camera space

		init_ray(game, &ray, camera_x);
		ray_caster(game, &ray, &wall);

		int lineHeight = abs((GAME_LY) / wall.dist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = (-lineHeight / 2 + GAME_LY / 2);
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + (GAME_LY / 2);
		if(drawEnd >= GAME_LY)
			drawEnd = (GAME_LY) - 1;


		double wallX;
		if (wall.side == 1)
			 wallX = ray.pos.x + ((wall.map.y - ray.pos.y + (1 - wall.step.y) / 2) / ray.dir.y) * ray.dir.x;
		else
			wallX = ray.pos.y + ((wall.map.x - ray.pos.x + (1 - wall.step.x) / 2) / ray.dir.x) * ray.dir.y;
		wallX -= floor(wallX);

		int texX = TEX_SIZE - wallX * TEX_SIZE;
		if(wall.side == 0 && ray.dir.x > 0) texX = TEX_SIZE - texX - 1;
		if(wall.side == 1 && ray.dir.y < 0) texX = TEX_SIZE - texX - 1;


		int y = drawStart;

		while (y <= drawEnd)
		{
			int texY = (y * 2 - GAME_LY + lineHeight)* (TEX_SIZE/2)/lineHeight;

			void *color;
			color = &((Uint8 *)(game->map.textures[wall.id]->pixels))[texX * 3 + (texY * TEX_SIZE * 3)];
			if (wall.side == 1)
				game_draw_pixel_black(game, game->sdl.text_buf, GAME_X + (GAME_LX - x), GAME_Y + y, color);
			else
				game_draw_pixel(game, game->sdl.text_buf, GAME_X + (GAME_LX - x), GAME_Y + y, color);
			y++;
		}
		//y = (y < 0) ? 0 : y;
		draw_floor_and_ceil(game, GAME_LX - x, y, ray, &wall, wallX);
		game->zbuffer[x] = wall.dist;

	}
	game_draw_sprites(game);
}
