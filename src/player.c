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

void	player_move(t_player *player, t_game *game, KEY dir)
{
	t_vect2dd	new;
	t_vect2dd	tmp_dir;

	if (dir == UP)
	{
		new.x = player->pos.x + (player->dir.x * game->dt * 5 * -(game->input[UP] / 32767.0));
		new.y = player->pos.y + (player->dir.y * game->dt * 5 * -(game->input[UP] / 32767.0));
	}
	else if (dir == DOWN)
	{
		new.x = player->pos.x - (player->dir.x * game->dt * 5);
		new.y = player->pos.y - (player->dir.y * game->dt * 5);
	}
	else if (dir == LEFT)
	{
		printf("left = %d\n", game->input[LEFT]);
		tmp_dir = vect2dd_rotate(player->dir, M_PI_2);
		new.x = player->pos.x + (tmp_dir.x * game->dt * 2 * -(game->input[LEFT] / 32767.0));
		new.y = player->pos.y + (tmp_dir.y * game->dt * 2 * -(game->input[LEFT] / 32767.0));
	}
//	else if (dir == RIGHT)
//	{
//		tmp_dir = vect2dd_rotate(player->dir, M_PI + M_PI_2);
//		new.x = player->pos.x + (tmp_dir.x * game->dt * 2);
//		new.y = player->pos.y + (tmp_dir.y * game->dt * 2);
//	}
	if (game->map.data[(int)new.x + ((int)new.y * game->map.lx)] == 0)
	{
		player->pos.x = new.x;
		player->pos.y = new.y;
	}
}

void	player_update(t_player *player, t_game *game)
{
	double new_pos_x;
	double new_pos_y;

	if (game->input[MOUSE_X])
	{
		double motion = (-game->input[MOUSE_X] / 100.0) * 2 * M_PI * game->dt;
		//printf("%f \n",motion);
		player->dir = vect2dd_rotate(player->dir, motion);
		player->plane = vect2dd_rotate(player->plane, motion);
		game->input[MOUSE_X] = 0;
	}

	if (game->input[UP])
		player_move(&(game->player), game, UP);
	if (game->input[DOWN])
		player_move(&(game->player), game, DOWN);
	if (game->input[RIGHT])
		player_move(&(game->player), game, RIGHT);
	if (game->input[LEFT])
		player_move(&(game->player), game, LEFT);
	if (game->input[TURN_LEFT])
	{
		double motion = M_PI_2 * game->dt;
		player->dir = vect2dd_rotate(player->dir, motion);
		player->plane = vect2dd_rotate(player->plane, motion);
	}
	if (game->input[TURN_RIGHT])
	{
		double motion = -M_PI_2 * game->dt;
		player->dir = vect2dd_rotate(player->dir, motion);
		player->plane = vect2dd_rotate(player->plane, motion);
	}

	//printf("%f, %f \n",game->player.pos.x, game->player.pos.y);
}
