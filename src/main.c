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

int		main(int ac, char **av)
{
	t_game		game;


	game.dt = 0;

	int i = 0;

	game_init_sdl(&game);
<<<<<<< HEAD
	map_init(&game, 1, 1);
=======
	if (ac == 2)
		map_init(&game, 1, ft_atoi(av[1]));
	else
		map_init(&game, 1, 1);
>>>>>>> branch 'master' of https://github.com/spectrenoir06/wolf3d_42.git

	for (i = ((GAME_LY) / 2); i < (GAME_LY); i++)
		game.calcule[i - (GAME_LY / 2)] = (GAME_LY) / (2.0 * i - (GAME_LY));

	game_render(&game);
	hud_render(&game);
	hud_background(&game);
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
		//printf("%f ; %f\n",1/game.dt, game.dt);

	}
	return (0);
}
