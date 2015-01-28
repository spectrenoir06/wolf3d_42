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
	player->pos.x = 22.5;
	player->pos.y = 40.5;
	player->dir.x = -1;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0.66;
	player->box.x = 0.2;
	player->box.y = 0.2;
	player->speed = 5;
	player->weapon = 1;
	player->w_anim = 0;
}

int		player_collide_world(t_map *map, t_player *player)
{
	t_vect2dd	test;

	test.x = player->pos.x - player->box.x / 2.0;
	test.y = player->pos.y - player->box.y / 2.0;
	if (test.x >= 0 && test.y >= 0 && map_get_block(map, map->wall,test))
		return (1);
	test.x += player->box.x;
	if (test.x <= map->lx && test.y >= 0 && map_get_block(map, map->wall, test))
		return (1);
	test.y += player->box.y;
	test.x -= player->box.x;
	if (test.x >= 0 && test.y <= map->ly && map_get_block(map, map->wall, test))
		return (1);
	test.x += player->box.x;
	if (test.x <= map->lx && test.y <= map->ly && map_get_block(map, map->wall, test))
		return (1);
	return (0);
}

void	player_move(t_player *player, t_game *game, KEY dir)
{
	t_vect3dd	save;
	t_vect2dd	tmp_dir;

	save = player->pos;
	if (dir == MOV_Y)
	{
		player->pos.x += (player->dir.x * game->dt * player->speed * (game->input[MOV_Y] / 32767.0));
		player->pos.y += (player->dir.y * game->dt * player->speed * (game->input[MOV_Y] / 32767.0));
	}
	else if (dir == MOV_X)
	{
		tmp_dir = vect2dd_rotate(player->dir, M_PI_2);
		player->pos.x += (tmp_dir.x * game->dt * 2 * -(game->input[MOV_X] / 32767.0));
		player->pos.y += (tmp_dir.y * game->dt * 2 * -(game->input[MOV_X] / 32767.0));
	}
	if (player_collide_world(&(game->map), player))
	{
		player->pos.x = save.x;
		player->pos.y = save.y;
		//SDL_HapticRumbleStop(game->haptic);
	}
	//else
		//SDL_HapticRumblePlay(game->haptic, 0.5, 10000);
	if (!Mix_Playing(1))
		Mix_PlayChannel(1, game->sounds.pas, 0);
}

void	player_update(t_player *player, t_game *game)
{
	double new_pos_x;
	double new_pos_y;

	if (game->input[ROT_Z_M])
	{
		double motion = (game->input[ROT_Z_M] / 100.0) * 2 * M_PI * game->dt;
		//printf("%f \n",motion);
		player->dir = vect2dd_rotate(player->dir, motion);
		player->plane = vect2dd_rotate(player->plane, motion);
		game->input[ROT_Z_M] = 0;
	}

	if (game->input[MOV_Y])
		player_move(&(game->player), game, MOV_Y);
	if (game->input[MOV_X])
	{
		player_move(&(game->player), game, MOV_X);
	}
	if (game->input[ROT_Z])
	{
		double motion = M_PI_2 * game->dt  * (game->input[ROT_Z] / 32767.0);
		player->dir = vect2dd_rotate(player->dir, motion);
		player->plane = vect2dd_rotate(player->plane, motion);
	}
	//printf("%f, %f \n",game->player.pos.x, game->player.pos.y);
}
