/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joystick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 17:31:29 by adoussau          #+#    #+#             */
/*   Updated: 2015/02/04 17:31:31 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	joy_but_down(SDL_Event ev, t_game *game)
{
	if (ev.jbutton.button == 11)
		game->input[MOV_Y] = SINT16_MAX;
	else if (ev.jbutton.button == 12)
		game->input[MOV_Y] = SINT16_MIN;
	else if (ev.jbutton.button == 13)
		game->input[MOV_X] = SINT16_MIN;
	else if (ev.jbutton.button == 14)
		game->input[MOV_X] = SINT16_MAX;
	else if (ev.jbutton.button == 4)
		game->input[ROT_Z] = SINT16_MIN;
	else if (ev.jbutton.button == 5)
		game->input[ROT_Z] = SINT16_MAX;
	else if (ev.jbutton.button == 6)
		game->player.speed += 2;
	else if (ev.jbutton.button == 0)
		SDL_HapticRumblePlay(game->haptic, 0.8, SDL_HAPTIC_INFINITY);
	else if (ev.jbutton.button == 10)
		sdl_exit(game);
}

void	joy_but_up(SDL_Event ev, t_game *game)
{
	if (ev.jbutton.button == 11 || ev.jbutton.button == 12)
		game->input[MOV_Y] = 0;
	else if (ev.jbutton.button == 13 || ev.jbutton.button == 14)
		game->input[MOV_X] = 0;
	else if (ev.jbutton.button == 4 || ev.jbutton.button == 5)
		game->input[ROT_Z] = 0;
	else if (ev.jbutton.button == 0)
		SDL_HapticRumbleStop(game->haptic);
	else if (ev.jbutton.button == 6)
		game->player.speed -= 2;
	Mix_FadeOutChannel(1, 200);
}

void	joy_axis(SDL_Event ev, t_game *game)
{
	if (ev.jaxis.axis == 1 && (ev.jaxis.value > 5000 || ev.jaxis.value < -5000))
		game->input[MOV_Y] = -ev.jaxis.value - 1;
	else if (ev.jaxis.axis == 1)
		game->input[MOV_Y] = 0, Mix_FadeOutChannel(1, 200);
	if (ev.jaxis.axis == 0 && (ev.jaxis.value > 5000 || ev.jaxis.value < -5000))
		game->input[MOV_X] = -ev.jaxis.value - 1;
	else if (ev.jaxis.axis == 0)
		game->input[MOV_X] = 0, Mix_FadeOutChannel(1, 200);
	if (ev.jaxis.axis == 3 && (ev.jaxis.value > 5000 || ev.jaxis.value < -5000))
		game->input[ROT_Z] = ev.jaxis.value;
	else if (ev.jaxis.axis == 3)
		game->input[ROT_Z] = 0;
	if (ev.jaxis.axis == 5 && (ev.jaxis.value > 5000)
		&& game->player.w_anim == 0)
	{
		weapon_start_anim(game, &game->player);
		Mix_PlayChannel(1, game->sounds.son2, 0);
	}
}
