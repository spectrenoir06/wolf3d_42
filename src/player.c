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
		new.x = player->pos.x + (player->dir.x * game->dt * 5);
		new.y = player->pos.y + (player->dir.y * game->dt * 5);
	}
	else if (dir == DOWN)
	{
		new.x = player->pos.x - (player->dir.x * game->dt * 5);
		new.y = player->pos.y - (player->dir.y * game->dt * 5);
	}
	else if (dir == LEFT)
	{
		tmp_dir = vect2dd_rotate(player->dir, M_PI_2);
		new.x = player->pos.x + (tmp_dir.x * game->dt * 2);
		new.y = player->pos.y + (tmp_dir.y * game->dt * 2);
	}
	else if (dir == RIGHT)
	{
		tmp_dir = vect2dd_rotate(player->dir, M_PI + M_PI_2);
		new.x = player->pos.x + (tmp_dir.x * game->dt * 2);
		new.y = player->pos.y + (tmp_dir.y * game->dt * 2);
	}
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
		double motion = -game->input[MOUSE_X] / 200.0;
		//printf("%f \n",motion);
		double oldDirX = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(motion) - game->player.dir.y * sin(motion);
		game->player.dir.y = oldDirX * sin(motion) + game->player.dir.y * cos(motion);
		double oldPlaneX = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cos(motion) - game->player.plane.y * sin(motion);
		game->player.plane.y = oldPlaneX * sin(motion) + game->player.plane.y * cos(motion);
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
		 double oldDirX = game->player.dir.x;
		 game->player.dir.x = game->player.dir.x * cos(game->dt) - game->player.dir.y * sin(game->dt);
		 game->player.dir.y = oldDirX * sin(game->dt) + game->player.dir.y * cos(game->dt);
		 double oldPlaneX = game->player.plane.x;
		 game->player.plane.x = game->player.plane.x * cos(game->dt) - game->player.plane.y * sin(game->dt);
		 game->player.plane.y = oldPlaneX * sin(game->dt) + game->player.plane.y * cos(game->dt);
	}
	if (game->input[TURN_RIGHT])
	{
		double oldDirX = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(-game->dt) - game->player.dir.y * sin(-game->dt);
		game->player.dir.y = oldDirX * sin(-game->dt) + game->player.dir.y * cos(-game->dt);
		double oldPlaneX = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cos(-game->dt) - game->player.plane.y * sin(-game->dt);
		game->player.plane.y = oldPlaneX * sin(-game->dt) + game->player.plane.y * cos(-game->dt);
	}

	//printf("%f, %f \n",game->player.pos.x, game->player.pos.y);
}
