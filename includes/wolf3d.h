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
# include "libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <string.h>
# include "libft.h"

# ifdef __APPLE__
#  include "SDL2/SDL.h"
#  include "SDL_mixer.h"
# elif __linux
#  include <SDL2/SDL.h>
#  include <SDL/SDL_mixer.h>
# endif

# define WIN_X 1600
# define WIN_Y 900
# define GAME_X 40
# define GAME_Y 20
# define GAME_LX 1520
# define GAME_LY 660
# define TEX_SIZE 512
# define SINT16_MAX 32767
# define SINT16_MIN -32768.0
# define DSINT16_MAX 32767.0

//# define NBSPRITE 5
# define NB_SPRITE_TEX 5
# define NB_WEAPON_TEX 1
# define NB_WEAPON_TEX_FRAME 5
# define NB_ENTITY_MAX 100

# define WALL 0x00FF00
# define FLOOR 0xFF0000
# define PLAYER 0x0000FF
# define FACE 0x0099FF

//# define MUSICS_REP modes/1/maps/1/music
//# define SOUNDS_REP modes/1/maps/1/sfx

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

typedef struct s_rectdd
{
	double		x;
	double		y;
	double		w;
	double		h;
}				t_rectdd;

typedef struct 		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct	s_entity
{
	t_vect2dd	pos;
	t_vect2dd	dir;
	int			texture;
	int			tex_anim;
	int			tex_focus;
	double		dist;
	int			type;
}				t_entity;

typedef struct s_sprite
{
	SDL_Surface	*tex;
	int			frames;
}				t_sprite;

typedef struct	s_player
{
	t_vect3dd	pos;
	t_vect2dd	dir;
	t_vect2dd	plane;
	t_vect2dd	box;
	int			speed;
	char		weapon;
	float		w_anim;
}				t_player;

typedef struct s_sounds
{
	Mix_Chunk	*pas;
	Mix_Chunk	*son1;
	Mix_Chunk	*son2;
	Mix_Chunk 	*son3;
	Mix_Chunk 	*son4;
	Mix_Chunk 	*son5;
	Mix_Chunk 	*son6;
	Mix_Music	*music;
}				t_sounds;

typedef struct s_sdl
{
	SDL_Window			*win;
	SDL_Texture			*tex;
	SDL_Renderer		*rd;
	Uint32				*text_buf;
	Uint32				*hud_buf;
	int					lx;
	int					ly;

}			t_sdl;

typedef struct s_map
{
	int			lx;
	int			ly;
	int			nb_entity;
	int			nb_texture;
	Uint8		*floor;												// malloc
	Uint8		*wall;												// malloc
	Uint8		*ceil;												// malloc
	SDL_Surface **textures;											// malloc pointeur + SDL_SURFACE
	SDL_Surface *sky;												// 					 SDL_SURFACE
	t_entity	entity[NB_ENTITY_MAX];								// non malloc
	t_entity	*entity_ptr[NB_ENTITY_MAX];							// non malloc
	t_sprite 	sprite[NB_SPRITE_TEX];								// non malloc
	SDL_Surface *weapon_tex[NB_WEAPON_TEX + 1][NB_WEAPON_TEX_FRAME + 1];	// a bouger
	double		calcule[GAME_LY / 2];
}				t_map;

typedef struct s_game
{
	t_sdl				sdl;
	t_player			player;
	t_map				map;
	double				dt;
	t_color				texture[TEX_SIZE][TEX_SIZE];
	Sint16				input[12];
	SDL_Joystick		*joystick;
	SDL_Haptic			*haptic;
	double				Zbuffer[WIN_X];
	t_sounds			sounds;
	double				calcule[GAME_LY];
}						t_game;

typedef	struct	s_ray
{
	t_vect2dd	pos;
	t_vect2dd	dir;
	t_vect2dd	delta;
	t_vect2dd	side;
}				t_ray;

typedef struct s_wall
{
	t_vect2di	map;
	double		dist;
	int			side;
	int			id;
	t_vect2di	step;
}				t_wall;

void	ft_kebab(char * buff, const char * first, ...);

t_vect2dd	vect2dd_rotate(t_vect2dd vect, double angle);
double		get_vect2dd_angle(t_vect2dd vect);

void	bmp_draw(t_game *game, SDL_Surface *img, int startx, int starty);

void	game_init_sdl(t_game *game);
void	game_draw_all(t_game *game);
void	game_draw_pixel(t_game *game, Uint32 *buf, int x, int y, void *c);
void	game_render(t_game *game);
void	game_draw_rect(t_game *game, Uint32 *buf, int x, int y, int lx, int ly, int color);
int		game_event_handler(t_game *game);

void	player_init(t_player *player);
void	player_update(t_player *player, t_game *game);
void	player_move(t_player *player,t_game *game, KEY dir);

void	sprite_load(t_map *map, char *path);
void	map_init(t_game *game, int mode, int map);
int		map_load(t_map *map, char *path);
inline int		map_get_block(t_map *map, Uint8 *data, t_vect2dd pt);
void	sprite_load(t_map *map, char *path);

void	game_init_sdl_mixer(t_sounds *sounds);
void	sounds_init(t_sounds *sounds);
void	sdl_mixer_quit(t_sounds *sounds);

void	hud_background(t_game *game);
void	hud_render(t_game *game);
void	hud_map(t_game *game);

int		weapon_load(t_map *map, char *path, int n);
void	weapon_start_anim(t_game *game, t_player *player);
int		weapon_animate(t_game *game, t_player *player);
void	weapon_draw(t_game *game);

void	hud_background(t_game *game);
int		map_get_block(t_map *map, Uint8 *data, t_vect2dd pt);
void	player_init(t_player *player);
void	ft_kebab(char * buff, const char * first, ...);

#endif
