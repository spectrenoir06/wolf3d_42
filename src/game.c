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
	game->sdl.hud_buf = malloc(sizeof(Uint32) * game->sdl.lx * game->sdl.ly);
	if (game->sdl.text_buf == NULL || game->sdl.hud_buf == NULL)
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



void	game_draw_rect(t_game *game, Uint32 *buf, int x, int y, int lx, int ly, t_color c)
{
	int a = x;
	int b = y;

	while (a < (x + lx))
	{
		b = y;
		while (b < (y + ly))
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

//void	draw_ceil(t_game *game,int x, int end)
//{
//	int y = 0;
//	while (y < end)
//	{
//		game_draw_pixel(game,x,y, game->map.color_ceil);
//		y++;
//	}
//}
//
//void	draw_floor(t_game *game,int x, int y)
//{
//	while (y < game->sdl.ly)
//	{
//		game_draw_pixel(game,x,y, game->map.color_floor);
//		y++;
//	}
//}

void	draw_floor_and_ceil(t_game *game, int x, int y, t_ray ray, t_wall *wall, double wallX)
{
	//printf("%d\n",y);
	t_vect2dd	floor;
	double		weight;// coefficient de ponderation
	t_vect2dd	current_floor;
	t_vect2dd	floor_tex;
	//double		currentDist;// point de depart de la texture

	if (wall->side == 0 && ray.dir.x > 0) {
		// nord
		floor.x = wall->map.x;
		floor.y = wall->map.y + wallX;
	} else if (wall->side == 0 && ray.dir.x < 0) {
		// sud
		floor.x = wall->map.x + 1.0;
		floor.y = wall->map.y + wallX;
	} else if (wall->side == 1 && ray.dir.y > 0) {
		// est
		floor.x = wall->map.x + wallX;
		floor.y = wall->map.y;
	} else {
		// ouest
		floor.x = wall->map.x + wallX;
		floor.y = wall->map.y + 1.0;
	}

	while (y <= GAME_LY)
	{
		//currentDist = game->map.calcule[y];// distance
		//printf("%f\n",currentDist);
		weight = (game->map.calcule[y]) / (wall->dist);// coef
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

		if (!(color->r == 0xFF && color->g == 0x00 && color->b == 0xFF))
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, y + GAME_Y, color);						// trace le sol
		else
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, y + GAME_Y, &((Uint8 *)(game->map.sky->pixels))[x * 3 + (y *  (game->map.sky->w) * 3)]);

		if (!(color2->r == 0xFF && color2->g == 0x00 && color2->b == 0xFF))
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, GAME_LY + GAME_Y - y, color2);	// trace le plafond
		else
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, GAME_LY + GAME_Y - y, &((Uint8 *)(game->map.sky->pixels))[x * 3 + (((GAME_LY) - y) * (game->map.sky->w) * 3)]);
		y++;
		//SDL_Delay(32);
	}
}

int		sprite_compare(void *sprite1, void *sprite2)
{
	return (((t_sprite *)sprite2)->dist - ((t_sprite *)sprite1)->dist);
}

void	game_draw_sprites(t_game *game)
{
	int	y;
	int x;

   for(x = 0; x < game->map.nb_obj; x++)
	  game->map.sprite[x].dist = ((game->player.pos.x - game->map.sprite[x].pos.x) * (game->player.pos.x - game->map.sprite[x].pos.x) + (game->player.pos.y - game->map.sprite[x].pos.y) * (game->player.pos.y - game->map.sprite[x].pos.y));

	ft_sort_qck((void **)game->map.sprite_ptr,  game->map.nb_obj, sprite_compare);
	for(x = 0; x <  game->map.nb_obj; x++)
	{
		double	spritex = game->map.sprite_ptr[x]->pos.x - game->player.pos.x;
		double	spritey = game->map.sprite_ptr[x]->pos.y - game->player.pos.y;

		double	invdet = 1.0 / (game->player.plane.x * game->player.dir.y - game->player.dir.x * game->player.plane.y);

		double	transformX = invdet * (game->player.dir.y * spritex - game->player.dir.x * spritey);
		double	transformY = invdet * (-game->player.plane.y * spritex + game->player.plane.x * spritey);

		int		spriteScreenX = (int)(((GAME_LX) / 2.0) * (1 + transformX / transformY));

		int		spriteheight = abs((int)((GAME_LY) / transformY));

		int		drawStartY = -spriteheight / 2.0 + (GAME_LY) / 2.0;
		if (drawStartY < 0)
			drawStartY = 0;
		int		drawEndY = spriteheight / 2.0 + (GAME_LY) / 2.0;
		if (drawEndY >= (GAME_LY))
			drawEndY = (GAME_LY) - 1;

		int		spriteWidth = abs((int)((GAME_LY) / transformY));
		int		drawStartX = -spriteWidth / 2.0 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int		drawEndX = spriteWidth / 2.0 + spriteScreenX;
		if (drawEndX >= (GAME_LX))
			drawEndX = (GAME_LX) - 1;

		int stripe;
		int	i;
		for (stripe = drawStartX; stripe <= drawEndX; stripe++)
		{
			int	texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 512 / spriteWidth / 256);

			if (transformY > 0 && stripe > 0 && stripe < (GAME_LX) && transformY < game->Zbuffer[stripe])
			{
				for (y = drawStartY; y < drawEndY; y++)
				{
					int	d = y - (GAME_LY) / 2.0 + spriteheight / 2.0;
					int	texY = ((d * 512) / spriteheight);

					t_color *color;
					double	angle;
					t_vect2dd	pos;
					pos.x = game->player.pos.x - game->map.sprite_ptr[x]->pos.x;
					pos.y = game->player.pos.y - game->map.sprite_ptr[x]->pos.y;
					angle = atan2(pos.y, pos.x) - atan2(game->map.sprite_ptr[x]->dir.y, game->map.sprite_ptr[x]->dir.x) + M_PI_4 / 2;
					if (angle < 0)
						angle += 2 * M_PI;
					i = ((angle) / (M_PI * 2.0) * 8.0);
					if (i > 7)
						i = 7;
					if (i < 0)
						i = 0;
					color = (t_color *) &((Uint8*)(game->map.sprite_tex[game->map.sprite_ptr[x]->texture][i]->pixels))[(int)texX * 3 + (texY * 3 * 512)];
					if (!(color->r == 0xFF && color->g == 0x00 && color->b == 0xFF))
						game_draw_pixel(game, game->sdl.text_buf, GAME_X + GAME_LX - stripe, GAME_Y +  y, color);
				}
//				printf("angle2 -> %d\n", i);
			}
		}
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
			//int texY = (y - drawStart) * TEX_SIZE / (drawEnd - drawStart);

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
		game->Zbuffer[x] = wall.dist;

	}
	game_draw_sprites(game);
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
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT && game->player.w_anim == 0)
			weapon_start_anim(game, &game->player), Mix_PlayChannel(1, game->sounds.son2, 0);
	}
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
			game->input[MOV_Y] = SINT16_MAX;
		else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
			game->input[MOV_Y] = SINT16_MIN;
		else if (event.key.keysym.sym == SDLK_a)
			game->input[MOV_X] = SINT16_MAX;
		else if (event.key.keysym.sym == SDLK_d)
			game->input[MOV_X] = SINT16_MIN;
		else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q)
			game->input[ROT_Z] = SINT16_MIN;
		else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_e)
			game->input[ROT_Z] = SINT16_MAX;
		else if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
			game->player.speed += 3;
		else if (event.key.keysym.sym == SDLK_SPACE && game->player.w_anim == 0)
				weapon_start_anim(game, &game->player), Mix_PlayChannel(1, game->sounds.son2, 0);
		else if (event.key.keysym.sym == SDLK_p)
			{
				if(Mix_PausedMusic())
					Mix_ResumeMusic();
				else if (Mix_PlayingMusic())
					Mix_PauseMusic();
			}
		else if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_JoystickClose(0);
			SDL_DestroyWindow(game->sdl.win);
			sdl_mixer_quit(&game->sounds);
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
		Mix_FadeOutChannel(1, 200);
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
		else if (event.jbutton.button == 0)
		{
			SDL_HapticRumblePlay(game->haptic, 0.8, SDL_HAPTIC_INFINITY);
			// jouer son
		}
		else if (event.jbutton.button == 10)
		{
			SDL_JoystickClose(0);
			SDL_DestroyWindow(game->sdl.win);
			sdl_mixer_quit(&game->sounds);
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
		else if (event.jbutton.button == 0)
			SDL_HapticRumbleStop(game->haptic);
		else if (event.jbutton.button == 6)
			game->player.speed -= 3;
		Mix_FadeOutChannel(1, 200);
	}
	else if (event.type == SDL_JOYAXISMOTION)
	{
		double test;
		if (event.jaxis.axis == 1 && (event.jaxis.value > 5000 || event.jaxis.value < -5000))
			game->input[MOV_Y] = event.jaxis.value;
		else if (event.jaxis.axis == 1)
			game->input[MOV_Y] = 0, Mix_FadeOutChannel(1, 200);
		if (event.jaxis.axis == 0 && (event.jaxis.value > 5000 || event.jaxis.value < -5000))
			game->input[MOV_X] = event.jaxis.value;
		else if (event.jaxis.axis == 0)
			game->input[MOV_X] = 0, Mix_FadeOutChannel(1, 200);
		if (event.jaxis.axis == 3 && (event.jaxis.value > 5000 || event.jaxis.value < -5000))
			game->input[ROT_Z] = event.jaxis.value;
		else if (event.jaxis.axis == 3)
			game->input[ROT_Z] = 0;
		if (event.jaxis.axis == 5 && (event.jaxis.value > 5000) && game->player.w_anim == 0)
					weapon_start_anim(game, &game->player), Mix_PlayChannel(1, game->sounds.son2, 0);

	}
	else if (event.type == SDL_QUIT)
	{
		SDL_JoystickClose(0);
		SDL_DestroyWindow(game->sdl.win);
		sdl_mixer_quit(&game->sounds);
		SDL_Quit();
		exit(0);
	}

	/*									BRUIT SUPER CHIANT QUI VIENS DE NUL PART
	int angle;
	angle = 40 * get_vect2dd_angle(game->player.dir);
	printf("%d", angle);
	if (!Mix_Playing(0))
			Mix_PlayChannel(0, game->sounds.son1, 1);
	Mix_SetDistance(0, sqrt((game->player.pos.x * game->player.pos.x) + (game->player.pos.y * game->player.pos.y)) * 4);
	Mix_SetPanning(0, 200 - angle, 200 + angle);
	*/

	return (1);
}
