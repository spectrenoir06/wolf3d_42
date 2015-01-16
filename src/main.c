/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:55:44 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/13 16:55:46 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

struct timeval tv1, tv2;



int		main(void)
{

	SDL_Event	event;
	t_game		game;
	t_color		color = {0xFF,0xFF,0xFF,0xFF};
	t_color		color2 = {0xFF,0x00,0x00,0xFF};

	game.player.pos.x = 10;
	game.player.pos.y = 10;

	game.player.dir.x = 0;
	game.player.dir.y = 0;

	game.dt = 0;

	int i = 0;
	int j = 0;

	SDL_Surface *imageDeFond = SDL_LoadBMP("img/stones.bmp");
	//SDL_LockSurface(imageDeFond);


	while (i<256)
	{
		j = 0;
		while (j<256)
		{
			game.texture[i][j].r = ((Uint8*)(imageDeFond->pixels))[i * 3 + (j * 3 * 256)];
			game.texture[i][j].g = ((Uint8*)(imageDeFond->pixels))[i * 3 + (j * 3 * 256) + 1];
			game.texture[i][j].b = ((Uint8*)(imageDeFond->pixels))[i * 3 + (j * 3 * 256) + 2];
			j++;
		}
		i++;
	}


	SDL_Init(SDL_INIT_VIDEO);
	game_init_sdl(&game);
	game_init_map(&game);
	game_render(&game);
	game_draw_map(&game);
	game_draw_rect(&game, game.player.pos.x * 4, game.player.pos.y * 4, 2 , 2, color);
	game_draw_rect(&game, game.player.pos.x * 4 + (game.player.dir.x * 4), game.player.pos.y * 4 + (game.player.dir.y * 4), 2 , 2, color2);
	game_draw_all(&game);
	while (42)
	{
		tv2 = tv1;
		gettimeofday(&tv1, NULL);
		game.dt = ((tv1.tv_sec - tv2.tv_sec) + ((tv1.tv_usec - tv2.tv_usec) / 1000000.0)); //frametime is the time this frame has taken, in seconds

		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN)

			game_key_down(&game, &event);
			game_render(&game);
			game_draw_map(&game);
			game_draw_rect(&game, game.player.pos.x * 4, game.player.pos.y * 4, 2 , 2, color);
			game_draw_rect(&game, game.player.pos.x * 4 + (game.player.dir.x * 4), game.player.pos.y * 4 + (game.player.dir.y * 4), 2 , 2, color2);
			game_draw_all(&game);
		//}
		//printf("%f ; %f\n",game.player.plane.x, game.player.plane.y);

		/*game_render(&game);
					game_draw_map(&game);
					game_draw_rect(&game, game.player.pos.x * 4, game.player.pos.y * 4, 2 , 2, color);
					game_draw_rect(&game, game.player.pos.x * 4 + (game.player.dir.x * 4), game.player.pos.y * 4 + (game.player.dir.y * 4), 2 , 2, color2);
					game_draw_all(&game);*
		//printf("%f , dt = %f\n",1 / dt, dt); //FPS counter*/
	}
	return (0);
}
