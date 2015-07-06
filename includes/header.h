/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

void		ft_kebab(char *buff, const char *first, ...);

t_vect2dd	vect2dd_rotate(t_vect2dd vect, double angle);
double		get_vect2dd_angle(t_vect2dd vect);

void		bmp_draw(t_game *game, SDL_Surface *img, int startx, int starty);

void		game_init_sdl(t_game *game);
void		game_draw_all(t_game *game);
void		game_draw_pixel(t_game *game, int x, int y, int *c);
void		game_draw_pixel_black(t_game *game, int x, int y, int *c);
void		game_draw_rect(t_game *game, int x, int y, int color);
void		game_draw_sprites(t_game *game);
int			sprite_compare(void *entity1, void *entity2);
int			game_event_handler(t_game *game);
void		draw_floor_and_ceil(t_game *game, t_rend *rend);

void		init_ray(t_game *game, t_ray *ray, double camera_x);
void		ray_caster(t_game *game, t_ray *ray, t_wall *wall);

void		render_ray_calc(t_game *game, t_rend *rend);
void		render_pix_calc(t_rend *rend);
void		render(t_game *game, t_rend *rend);
void		game_render(t_game *game);

void		player_init(t_game *game);
void		player_update(t_player *player, t_game *game);
void		player_move(t_player *player, t_game *game, t_key dir);

void		sprite_load(t_map *map, char *path);
void		map_init(t_game *game, int mode, int map);
int			map_load(t_map *map, char *path);
int			map_get_block(t_map *map, Uint8 *data, t_vect2dd pt);

void		game_init_sdl_mixer(t_sounds *sounds, char *path);
void		sounds_init(t_sounds *sounds, char *path);
void		sdl_mixer_quit(t_sounds *sounds);

void		hud_background(t_game *game, int mode);
void		hud_render(t_game *game);
void		hud_map(t_game *game);

int			weapon_load(t_map *map, char *path, int n);
void		weapon_start_anim(t_game *game, t_player *player);
int			weapon_animate(t_game *game, t_player *player);
void		weapon_draw(t_game *game);

void		sdl_exit(t_game *game);
void		map_unload(t_map *map);
void		weapon_unload(t_map *map);

void		kb_key_down(SDL_Event ev, t_game *game);
void		kb_key_up(SDL_Event ev, t_game *game);
void		joy_but_down(SDL_Event ev, t_game *game);
void		joy_but_up(SDL_Event ev, t_game *game);
void		joy_axis(SDL_Event ev, t_game *game);

void		map_load_data(t_map *map, char *path, t_mapload *ml);
void		map_load_entity(t_map *map, t_mapload *ml);

int			multi_init(t_game *game);
void		multi_send_pos(t_game *game);

#endif
