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
	player->box.x = 0.2;
	player->box.y = 0.2;
	player->speed = 5;
}

int		player_collide_world(t_map *map, t_player *player)
{
	t_vect2dd	test;

	test.x = player->pos.x - player->box.x / 2.0;
	test.y = player->pos.y - player->box.y / 2.0;
	if (test.x >= 0 && test.y >= 0 && map_get_block(map, test))
		return (1);
	test.x += player->box.x;
	if (test.x <= map->lx && test.y >= 0 && map_get_block(map, test))
		return (1);
	test.y += player->box.y;
	test.x -= player->box.x;
	if (test.x >= 0 && test.y <= map->ly && map_get_block(map, test))
		return (1);
	test.x += player->box.x;
	if (test.x <= map->lx && test.y <= map->ly && map_get_block(map, test))
		return (1);
	return (0);
}

void	player_move(t_player *player, t_game *game, KEY dir)
{
	t_vect3dd	save;
	t_vect2dd	tmp_dir;
	//double angle;
	double coef;
	double tmp_angle;

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
//		if (get_vect2dd_angle(player->pos) >= 0.17 || get_vect2dd_angle(player->pos) <= -0.17)
//		{
//
//		}

		double angle = get_vect2dd_angle(player->dir);
		printf("%f\n", angle);

			if (angle > M_PI_4 && angle < M_PI_2)
				tmp_angle = M_PI_4;
			else if (angle > (3 * -M_PI_4) && angle < -M_PI_2)
				tmp_angle = (3 * -M_PI_4);
			else if (angle > (3 * M_PI_4) && angle < M_PI)
				tmp_angle = (3 * M_PI_4);
			else if (angle > -M_PI && angle < (3 * -M_PI_4))
				tmp_angle = (3 * -M_PI_4);
			else if (angle > M_PI_2 && angle < (3 * M_PI_4))//ok
				tmp_angle = (3 * M_PI_4);
			else if (angle > -M_PI_2 && angle < -M_PI_4)
				tmp_angle = -M_PI_4;
			else if (angle > -M_PI_4 && angle < 0)//ok
				tmp_angle = -M_PI_4;
			else if (angle > 0 && angle < M_PI_4)//ok
				tmp_angle = M_PI_4;


			tmp_dir = angle_to_vect2dd(tmp_angle);
			coef = cos(get_vect2dd_angles(player->dir, tmp_dir));
			save = player->pos;
			player->pos.x += (tmp_dir.x * coef * game->dt * 2);
			player->pos.y += (tmp_dir.y * coef * game->dt * 2);
			if (player_collide_world(&(game->map), player))
				player->pos = save;

//		if (angle > M_PI_2 && angle < M_PI)
//		{
//			tmp_dir.x = 1;
//			tmp_dir.y = 0;
//			coef = cos(angle);
//			player->pos.x += (tmp_dir.x * coef * game->dt * 2);
//			player->pos.y += (tmp_dir.y * coef * game->dt * 2);
//		}
		//SDL_HapticRumbleStop(game->haptic);
	}
	//else
		//SDL_HapticRumblePlay(game->haptic, 0.5, 10000);
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
		player_move(&(game->player), game, MOV_X);
	if (game->input[ROT_Z])
	{
		double motion = M_PI_2 * game->dt  * (game->input[ROT_Z] / 32767.0);
		player->dir = vect2dd_rotate(player->dir, motion);
		player->plane = vect2dd_rotate(player->plane, motion);
	}

	//printf("%f, %f \n",game->player.pos.x, game->player.pos.y);
}
