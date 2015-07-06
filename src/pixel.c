/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

inline void	game_draw_pixel(t_game *game, int x, int y, int *c)
{
	game->sdl.text_buf[x + (y * game->sdl.lx)] = *c;
}

inline void	game_draw_pixel_black(t_game *game, int x, int y, int *c)
{
	int color = *c;

	//color &= 0xD7D7D7;

	unsigned char *tmp = (unsigned char*)&color;

	tmp[0] = tmp[0] >> 1;
	tmp[1] = tmp[1] >> 1;
	tmp[2] = tmp[2] >> 1;

	game->sdl.text_buf[x + (y * game->sdl.lx)] = color;
}

void		bmp_draw(t_game *game, SDL_Surface *img, int startx, int starty)
{
	int		x;
	int		y;
	t_color	color;

	x = 0;
	while (x < img->w && x + startx < game->sdl.lx)
	{
		y = 0;
		while (y < img->h && y + starty < game->sdl.ly)
		{
			color = ((t_color *)img->pixels)[x + (y * img->w)];
			if (!(color.r == 255 && color.g == 0 && color.b == 255))
				game_draw_pixel(game, x + startx, y + starty, &color);
			y++;
		}
		x++;
	}
}
