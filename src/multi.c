/*
 * multi.c
 *
 *  Created on: 13 févr. 2015
 *      Author: spectrenoir
 */

#include "wolf3d.h"

typedef struct s_packet_player
{
	Uint32		x;
	Uint32		y;
	char		end;
}				t_packet_player;

void	multi_send_pos(t_game *game)
{
	t_packet_player packet;

	SDLNet_Write32((Uint32)game->player.pos.x, &packet.x);
	SDLNet_Write32((Uint32)game->player.pos.y, &packet.y);
	packet.end = '\n';

	ft_memcpy(&(game->multi.buffer), &game->player.pos.x, sizeof(double));
	ft_memcpy(&(game->multi.buffer[8]), &game->player.pos.y, sizeof(double));
	game->multi.buffer[16] = '\n';
	SDLNet_TCP_Send(game->multi.socket, game->multi.buffer,  17);
}

void	multi_recv_pos(t_game *game)
{

}
