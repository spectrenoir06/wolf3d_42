/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 19:13:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/13 19:13:50 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WIN_X 800
# define WIN_Y 480

typedef struct	s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
}				t_player;

typedef struct s_game
{
	SDL_Window			*win;
	SDL_Texture			*tex;
	SDL_Renderer		*rd;
	int					win_lx;
	int					win_ly;
	Uint32				*text_buf;
	int					dx;
	int					dy;
	int					x;
	int					y;
	Uint8				*map;
	t_player			player;
	double				plane_x;
	double				plane_y;

}						t_game;

typedef struct 		s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

#include "wolf3d.h"
#include <stdio.h>

void	game_init_sdl(t_game *game);
void	game_key_down(t_game *game, SDL_Event *event);
void	game_draw_all(t_game *game);
void	game_draw_pixel(t_game *game, int x, int y, t_color c);
void	game_render(t_game *game);

#endif
