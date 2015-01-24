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

int		weapon_load(t_game *game, t_map *map, int n)
{
	int	i;
	int	j;
	char	buff[255];

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < 5)
		{
			ft_kebab(buff, "modes/1/maps/1/weapons/", ft_itoa(i + 1), "/", ft_itoa(j + 1), ".bmp", NULL);
			ft_putendl(buff);
			map->weapon_tex[i + 1][j] = SDL_LoadBMP(buff);
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

void	weapon_draw(t_game *game)
{
	int	x;
	int	y;
	t_color color;

	for(x = 0; x < 512; x++)
	{
		for(y = 0; y < 512; y++)
		{
			memcpy(&color, &((Uint8 *)game->map.weapon_tex[game->player.weapon][weapon_get_anim(&game->player)]->pixels)[x * 3 + (y * 3 * 512)], 3);
			if (!(color.r == 255 && color.g == 0 && color.b == 255))
				memcpy(&game->sdl.text_buf[x + game->sdl.lx / 2 - 256 + ((y + game->sdl.ly - 512) * game->sdl.lx)], &((Uint8 *)game->map.weapon_tex[game->player.weapon][weapon_get_anim(&game->player)]->pixels)[x * 3 + (y * 3* 512)], 3);
		}
	}
}
