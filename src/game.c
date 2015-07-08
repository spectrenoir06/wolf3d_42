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

void	joystick_init(t_game *game)
{
	SDL_JoystickEventState(SDL_ENABLE);
	game->joystick = SDL_JoystickOpen(0);
	game->haptic = SDL_HapticOpenFromJoystick(game->joystick);
	if (SDL_HapticRumbleInit(game->haptic))
		ft_putstr("Can not init haptic rumble\n");
}

void	game_init_sdl(t_game *game)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) < 0)
		exit(EXIT_FAILURE);
	SDL_CreateWindowAndRenderer(	WIN_LX,
									WIN_LY,
									SDL_WINDOW_RESIZABLE,
									&(game->sdl.win),
									&(game->sdl.rd)
								);

	game->sdl.tex = SDL_CreateTexture(	game->sdl.rd,
										SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STREAMING,
										WIN_LX,
										WIN_LY
										);
	SDL_SetWindowTitle(game->sdl.win, "Wolf3d");
	if (game->sdl.win == NULL)
	{
		ft_putstr("Wolf3D: Error windows can't load\n");
		exit(1);
	}
	game->sdl.text_buf = malloc(sizeof(Uint32) * WIN_LX * WIN_LY);
	if (game->sdl.text_buf == NULL)
	{
		ft_putstr("Wolf3D: Error can't allocate buffer\n");
		exit(1);
	}
	if (SDL_NumJoysticks() == 1)
		joystick_init(game);
	SDL_SetRelativeMouseMode(1);
}

void	game_draw_rect(t_game *game, int x, int y, uint32_t color)
{
	int		a;
	int		b;

	a = x;
	b = y;
	while (a < (x + 4))
	{
		b = y;
		while (b < (y + 4))
		{
			game_draw_pixel(game, a, b, &color);
			b++;
		}
		a++;
	}
}

void	game_draw_all(t_game *game)
{
//	SDL_Rect r = {GAME_X1, GAME_Y1, GAME_LX, GAME_LY};
	SDL_UpdateTexture(game->sdl.tex, 0, game->sdl.text_buf, WIN_LX * sizeof(Uint32));
	SDL_RenderCopy(game->sdl.rd, game->sdl.tex, NULL, NULL);
	SDL_RenderPresent(game->sdl.rd);
}

void	init_ray(t_game *game, t_ray *ray, double camera_x)
{
	ray->pos.x = game->player.pos.x;
	ray->pos.y = game->player.pos.y;
	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	ray->delta.x = sqrt(1 + (ray->dir.y * ray->dir.y) /
			(ray->dir.x * ray->dir.x));
	ray->delta.y = sqrt(1 + (ray->dir.x * ray->dir.x) /
			(ray->dir.y * ray->dir.y));
}
