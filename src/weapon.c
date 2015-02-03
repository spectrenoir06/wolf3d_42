/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

int		weapon_load(t_map *map, char *path, int n)
{
	int	i;
	int	j;
	char	buff[255];
	char	*nbi;
	char	*nbj;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < 5)
		{
			nbi = ft_itoa(i + 1);
			nbj = ft_itoa(j + 1);
			ft_kebab(buff, path, "weapons/", nbi, "/", nbj, ".bmp", NULL);
			ft_putendl(buff);
			map->weapon_tex[i + 1][j] = SDL_LoadBMP(buff);
			free(nbi);
			free(nbj);
			j++;
		}
		i++;
	}
	return (1);
}

void	weapon_start_anim(t_game *game, t_player *player)
{
	player->w_anim = 1.0;
	weapon_animate(game, player);
}

int		weapon_animate(t_game *game, t_player *player)
{
	float	last;

	last = player->w_anim;
	if (player->w_anim > 0)
		player->w_anim += game->dt * 15;
	if (player->w_anim > 5)
		player->w_anim = 0;
	return ((int)last != (int)player->w_anim);
}

int		weapon_get_anim(t_player *player)
{
	return (int)(player->w_anim);
}

void	bmp_draw(t_game *game, SDL_Surface *img, int startx, int starty)
{
	int	x;
	int	y;
	t_color color;

	for(x = 0; x < img->w && x + startx < game->sdl.lx; x++)
	{
		for(y = 0; y < img->h && y + starty < game->sdl.ly; y++)
		{
			color = ((t_color *)img->pixels)[x + (y * img->w)];
			if (!(color.r == 255 && color.g == 0 && color.b == 255))
				game_draw_pixel(game, game->sdl.text_buf, x + startx, y + starty, &color);
		}
	}
}

void	weapon_draw(t_game *game)
{
	bmp_draw(game, game->map.weapon_tex[(int)game->player.weapon][weapon_get_anim(&game->player)], game->sdl.lx / 2 - 256, (game->sdl.ly - 512 - 220));
}
