/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 17:54:05 by adoussau          #+#    #+#             */
/*   Updated: 2015/02/05 17:54:07 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	render_ray_calc(t_game *game, t_rend *rend)
{
	rend->camera_x = 2.0 * rend->x / (float)GAME_LX - 1;
	init_ray(game, &rend->ray, rend->camera_x);
	ray_caster(game, &rend->ray, &rend->wall);
	rend->linehgt = fabs((GAME_LY) / rend->wall.dist);
}

void	render_pix_calc(t_rend *rend)
{
	rend->drawstart = (-rend->linehgt / 2 + GAME_LY / 2);
	if (rend->drawstart < 0)
		rend->drawstart = 0;
	rend->drawend = rend->linehgt / 2 + (GAME_LY / 2);
	if (rend->drawend >= GAME_LY)
		rend->drawend = (GAME_LY) - 1;
	if (rend->wall.side == 1)
		rend->wallx = rend->ray.pos.x + ((rend->wall.map.y - rend->ray.pos.y +
			(1 - rend->wall.step.y) / 2) / rend->ray.dir.y) * rend->ray.dir.x;
	else
		rend->wallx = rend->ray.pos.y + ((rend->wall.map.x - rend->ray.pos.x +
			(1 - rend->wall.step.x) / 2) / rend->ray.dir.x) * rend->ray.dir.y;
	rend->wallx -= floor(rend->wallx);
	rend->tex_x = TEX_SIZE - rend->wallx * TEX_SIZE;
	if (rend->wall.side == 0 && rend->ray.dir.x > 0)
		rend->tex_x = TEX_SIZE - rend->tex_x - 1;
	if (rend->wall.side == 1 && rend->ray.dir.y < 0)
		rend->tex_x = TEX_SIZE - rend->tex_x - 1;
}

void	render(t_game *game, t_rend *rend)
{
	rend->y = rend->drawstart;
	while (rend->y <= rend->drawend)
	{
		rend->tex_y = (rend->y * 2 - GAME_LY + rend->linehgt) *
				(TEX_SIZE / 2) / rend->linehgt;
		rend->color = &((Uint8 *)(game->map.textures[rend->wall.id]->pixels))
						[rend->tex_x * 3 + (rend->tex_y * TEX_SIZE * 3)];
		if (game->map.has_notext)
			game_draw_pixel(game, GAME_X +
					(GAME_LX - rend->x), GAME_Y + rend->y,
					&game->map.colors[rend->wall.side]);
		else
		{
			if (rend->wall.side == 1)
				game_draw_pixel_black(game, GAME_X +
						(GAME_LX - rend->x), GAME_Y + rend->y, rend->color);
			else
				game_draw_pixel(game, GAME_X +
						(GAME_LX - rend->x), GAME_Y + rend->y, rend->color);
		}
		rend->y++;
	}
	draw_floor_and_ceil(game, rend);
}

void	game_render(t_game *game)
{
	t_rend	rend;

	rend.x = 0;
	while (rend.x < GAME_LX)
	{
		render_ray_calc(game, &rend);
		render_pix_calc(&rend);
		render(game, &rend);
		game->zbuffer[rend.x] = rend.wall.dist;
		rend.x++;
	}
	game_draw_sprites(game);
}
