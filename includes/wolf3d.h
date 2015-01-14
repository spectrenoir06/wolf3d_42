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

# define WIN_X 500
# define WIN_Y 500

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
	Uint16				*map;
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

#endif
