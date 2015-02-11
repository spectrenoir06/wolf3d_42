/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
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

struct timeval tv1;
struct timeval tv2;

void	setdt(t_game *game)
{
	tv2 = tv1;
	gettimeofday(&tv1, NULL);
	game->dt = ((tv1.tv_sec - tv2.tv_sec) +
	((tv1.tv_usec - tv2.tv_usec) / 1000000.0));
}

void	check_args(t_game *game, int ac, char *av[])
{
	if (ac == 2)
	{
		if (!ft_strcmp(av[1], "1"))
			map_init(game, 1, 1);
		else if (!ft_strcmp(av[1], "2"))
			map_init(game, 1, 2);
		else if (!ft_strcmp(av[1], "3"))
			map_init(game, 1, 3);
		else if (!ft_strcmp(av[1], "4"))
			map_init(game, 1, 4), game->map.has_notext = 1;
		else
			map_init(game, 1, 2);
	}
	else
		map_init(game, 1, 2);
}

int		main(int ac, char **av)
{
	t_game	game;
	char	*fps;
	int		i;

	game.dt = 0;
	gettimeofday(&tv1, NULL);
	game_init_sdl(&game);
	check_args(&game, ac, av);
	i = ((GAME_LY) / 2) - 1;
	while (i++ < (GAME_LY) - 1)
		game.calcule[(i) - (GAME_LY / 2)] = (GAME_LY) / (2.0 * (i) - (GAME_LY));
	while (42)
	{
		setdt(&game);
		while (game_event_handler(&game))
			;
		player_update(&game.player, &game);
		game_render(&game);
		hud_render(&game);
		game_draw_all(&game);
		fps = ft_itoa(1 / game.dt);
		SDL_SetWindowTitle(game.sdl.win, fps);
		free(fps);
	}
	return (0);
}
