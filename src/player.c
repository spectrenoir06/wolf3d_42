/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void	player_init(t_player *player)
{
	player->pos.x = 2.5;
	player->pos.y = 3.5;
	player->dir.x = -1;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0.66;
	player->speed = 5;
}

void	player_move(t_player *player, t_game *game, KEY dir)
{
	t_vect2dd	new;
	t_vect2dd	tmp_dir;

	if (dir == MOV_Y)
	{
		new.x = player->pos.x + (player->dir.x * game->dt * player->speed * (game->input[MOV_Y] / 32767.0));
		new.y = player->pos.y + (player->dir.y * game->dt * player->speed * (game->input[MOV_Y] / 32767.0));
	}
	else if (dir == MOV_X)
	{
		tmp_dir = vect2dd_rotate(player->dir, M_PI_2);
		new.x = player->pos.x + (tmp_dir.x * game->dt * 2 * -(game->input[MOV_X] / 32767.0));
		new.y = player->pos.y + (tmp_dir.y * game->dt * 2 * -(game->input[MOV_X] / 32767.0));
	}
	if (game->map.data[(int)new.x + ((int)new.y * game->map.lx)] == 0)
	{
		player->pos.x = new.x;
		player->pos.y = new.y;
		SDL_HapticRumbleStop(game->haptic);
	}
	else
		SDL_HapticRumblePlay(game->haptic, 0.5, 10000);
}

void	player_update(t_player *player, t_game *game)
{
	double new_pos_x;
	double new_pos_y;

//	if (game->input[ROT_Z])
//	{
//		double motion = (-game->input[ROT_Z] / 100.0) * 2 * M_PI * game->dt;
//		//printf("%f \n",motion);
//		player->dir = vect2dd_rotate(player->dir, motion);
//		player->plane = vect2dd_rotate(player->plane, motion);
//		game->input[ROT_Z] = 0;
//	}

	if (game->input[MOV_Y])
		player_move(&(game->player), game, MOV_Y);
	if (game->input[MOV_X])
		player_move(&(game->player), game, MOV_X);
	if (game->input[ROT_Z])
	{
		double motion = M_PI_2 * game->dt  * -(game->input[ROT_Z] / 32767.0);
		player->dir = vect2dd_rotate(player->dir, motion);
		player->plane = vect2dd_rotate(player->plane, motion);
	}

	//printf("%f, %f \n",game->player.pos.x, game->player.pos.y);
}
