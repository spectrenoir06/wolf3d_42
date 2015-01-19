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

# include <stdio.h>

# ifndef __APPLE__
#  include "SDL2/SDL.h"
# else
#  include <SDL2/SDL.h>
# endif

# define WIN_X 800
# define WIN_Y 480
# define SINT16_MAX 32767
# define SINT16_MIN -32768.0
# define DSINT16_MAX 32767.0

typedef enum KEY KEY;
enum KEY
{
	MOV_X	= 0,
	MOV_Y	= 1,
	MOV_Z	= 2,
	ROT_X	= 3,
	ROT_Y	= 4,
	ROT_Z	= 5,
	ROT_Z_M = 6,
	USE		= 7
};

typedef struct s_vect2di
{
	int		x;
	int		y;
}				t_vect2di;

typedef struct s_vect2dd
{
	double		x;
	double		y;
}				t_vect2dd;

typedef struct s_vect3di
{
	int		x;
	int		y;
	int		z;
}				t_vect3di;

typedef struct s_vect3dd
{
	double		x;
	double		y;
	double		z;
}				t_vect3dd;

typedef struct 		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_color;

typedef struct	s_player
{
	t_vect3dd	pos;
	t_vect2dd	dir;
	t_vect2dd	plane;
	int			speed;
}				t_player;


typedef struct s_sdl
{
	SDL_Window			*win;
	SDL_Texture			*tex;
	SDL_Renderer		*rd;
	Uint32				*text_buf;
	int					lx;
	int					ly;

}			t_sdl;

typedef struct s_map
{
	int			lx;
	int			ly;
	Uint8		*data;
	SDL_Surface *textures[10];
	t_color		color_ceil;
	t_color		color_floor;
}				t_map;

typedef struct s_game
{
	t_sdl				sdl;
	t_player			player;
	t_map				map;
	double				dt;
	t_color				texture[512][512];
	Sint16				input[12];
	SDL_Joystick		*joystick;
	SDL_Haptic			*haptic;
}						t_game;

t_vect2dd	vect2dd_rotate(t_vect2dd vect, double angle);

void	game_init_sdl(t_game *game);
void	game_draw_all(t_game *game);
void	game_draw_pixel(t_game *game, int x, int y, t_color c);
void	game_render(t_game *game);
void	game_draw_rect(t_game *game, int x, int y, int lx, int ly, t_color c);
int		game_event_handler(t_game *game);

void	player_update(t_player *player, t_game *game);
void	player_move(t_player *player,t_game *game, KEY dir);

void	map_init(t_game *game);
void	map_draw(t_game *game);
int		map_load(t_game *game, t_map *map, char *path);

#endif
