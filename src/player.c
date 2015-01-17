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

void	player_move(t_game *game, t_player *player, KEY dir)
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
