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
	t_game		game;


	game.dt = 0;

	int i = 0;
	int j = 0;

	game_init_sdl(&game);
	map_init(&game);

	for (i = (game.sdl.ly / 2); i < game.sdl.ly; i++)
		game.map.calcule[i] = game.sdl.ly / (2.0 * i - game.sdl.ly);

	player_init(&game.player);
	game_render(&game);
	hud_render(&game);
	hud_background(game);
	game_draw_all(&game);
	while (42)
	{
		tv2 = tv1;
		gettimeofday(&tv1, NULL);
		game.dt = ((tv1.tv_sec - tv2.tv_sec) + ((tv1.tv_usec - tv2.tv_usec) / 1000000.0)); //frametime is the time this frame has taken, in seconds

		while (game_event_handler(&game))
				;
		{
			player_update(&game.player, &game);	// update player
			game_render(&game);		// update screen
			hud_render(&game);
			game_draw_all(&game);	// update screen
		}
		printf("%f ; %f\n",1/game.dt, game.dt);

	}
	return (0);
}
