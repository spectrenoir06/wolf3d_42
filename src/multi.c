
#include "wolf3d.h"

typedef struct s_packet_player
{
	Uint32		x;
	Uint32		y;
	char		end;
}				t_packet_player;

int		multi_init(t_game *game)
{
	SDLNet_Init();
	SDLNet_ResolveHost(&game->multi.ip, "10.13.1.155",12346);

	game->multi.udp_socket = SDLNet_UDP_Open(0);
	if(!game->multi.udp_socket)
	{
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}


	int channel = SDLNet_UDP_Bind(game->multi.udp_socket, -1, &game->multi.ip);
	if(channel==-1) {
		printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
		// do something because we failed to bind
	}

	game->multi.packet =  SDLNet_AllocPacket(512);

	memcpy(game->multi.packet->data, "test",5);
	game->multi.packet->len = 5;

	int numsent=SDLNet_UDP_Send(game->multi.udp_socket, -1, game->multi.packet);
	if(!numsent) {
		printf("erreur debile\n");
		printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
		// do something because we failed to send
		// this may just be because no addresses are bound to the channel...
	}
	else
	{
		printf("send udp\n");
	}

	/*if ((game->multi.socket = SDLNet_TCP_Open(&game->multi.ip)))
		{
			ft_strcpy((char *)game->multi.buffer, "hello\n");

			multi_send_pos(game);
			SDLNet_TCP_Send(game->multi.socket, (void *)game->multi.buffer, ft_strlen((char *)game->multi.buffer));
			//SDLNet_TCP_Close(game->multi.socket);
			//SDLNet_Quit();
		}
		else
			fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
*/
	return (1);
}

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
/*
void	multi_recv_pos(t_game *game)
{

}
*/
