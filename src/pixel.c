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

inline void	game_draw_pixel(t_game *game, int x, int y, void *c)
{
	ft_memcpy(&game->sdl.text_buf[x + (y * game->sdl.lx)], c, 3);
}

inline void	game_draw_pixel_black(t_game *game, int x, int y, void *c)
{
	t_color	color;

	ft_memcpy(&color, c, 3);
	color.r = color.r >> 1;
	color.g = color.g >> 1;
	color.b = color.b >> 1;
	ft_memcpy(&game->sdl.text_buf[x + (y * game->sdl.lx)], &color, 3);
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
