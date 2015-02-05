#include "wolf3d.h"

void	ray_caster(t_game *game, t_ray *ray, t_wall *wall)
{
	int		hit;

	hit = 0;
	wall->map.x = (int)ray->pos.x;
	wall->map.y = (int)ray->pos.y;
	if (ray->dir.x < 0)
	{
		wall->step.x = -1;
		ray->side.x = (ray->pos.x - wall->map.x) * ray->delta.x;
	}
	else
	{
		wall->step.x = 1;
		ray->side.x = (wall->map.x + 1.0 - ray->pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		wall->step.y = -1;
		ray->side.y = (ray->pos.y - wall->map.y) * ray->delta.y;
	}
	else
	{
		wall->step.y = 1;
		ray->side.y = (wall->map.y + 1.0 - ray->pos.y) * ray->delta.y;
	}
	while (hit == 0)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			wall->map.x += wall->step.x;
			wall->side = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			wall->map.y += wall->step.y;
			wall->side = 1;
		}
		if (game->map.wall[wall->map.x + (wall->map.y * game->map.lx)] > 0)
		{
			wall->id = game->map.wall[wall->map.x +
									(wall->map.y * game->map.lx)];
			hit = 1;
		}
	}
	if (wall->side == 0)
		wall->dist = fabs((wall->map.x - ray->pos.x + (1 - wall->step.x) / 2)
				/ ray->dir.x);
	else
		wall->dist = fabs((wall->map.y - ray->pos.y + (1 - wall->step.y) / 2)
				/ ray->dir.y);
}

void	draw_floor_and_ceil(t_game *game, int x, int y, t_ray ray, t_wall *wall, double wallx)
{
	t_vect2dd	floor;
	double		weight;// coefficient de ponderation
	t_vect2dd	current_floor;
	t_vect2dd	floor_tex;

	if (wall->side == 0 && ray.dir.x > 0)
	{
		floor.x = wall->map.x;
		floor.y = wall->map.y + wallx;
	}
	else if (wall->side == 0 && ray.dir.x < 0)
	{
		floor.x = wall->map.x + 1.0;
		floor.y = wall->map.y + wallx;
	}
	else if (wall->side == 1 && ray.dir.y > 0)
	{
		floor.x = wall->map.x + wallx;
		floor.y = wall->map.y;
	}
	else
	{
		floor.x = wall->map.x + wallx;
		floor.y = wall->map.y + 1.0;
	}

	while (y <= GAME_LY)
	{
		weight = (game->calcule[y - (GAME_LY / 2)]) / (wall->dist);// coef
		current_floor.x = weight * floor.x + (1.0 - weight) * game->player.pos.x;// position sur X
		current_floor.y = weight * floor.y + (1.0 - weight) * game->player.pos.y;// position sur Y
		floor_tex.x = (int)(current_floor.x * TEX_SIZE) % TEX_SIZE;// position texel sur X
		floor_tex.y = (int)(current_floor.y * TEX_SIZE) % TEX_SIZE;// position texel sur Y

		t_color *color;

		Uint8 test = game->map.floor[((int)current_floor.x) + ((int)(current_floor.y) * game->map.lx)];
		Uint8 test2 = game->map.ceil[((int)current_floor.x) + ((int)(current_floor.y) * game->map.lx)];

		color = (void *)&((Uint8*)(game->map.textures[test2]->pixels))[(int)floor_tex.x * 3 + ((int)floor_tex.y * 3 * TEX_SIZE)];

		t_color *color2;

		color2 = (void *)&((Uint8*)(game->map.textures[test]->pixels))[(int)floor_tex.x * 3 + ((int)floor_tex.y * 3 * TEX_SIZE) + 0];

		double	angle = atan2(game->player.dir.y, game->player.dir.x);
		int	sky = x + (angle) / (M_PI) * (double)(game->map.sky->w);
		sky %= game->map.sky->w;
		if (!(color->r == 0xFF && color->g == 0x00 && color->b == 0xFF))
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, y + GAME_Y, color);// trace le sol
		else
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, y + GAME_Y, &((Uint8 *)(game->map.sky->pixels))[(sky) * 3 + (y *  (game->map.sky->w) * 3)]);
		if (!(color2->r == 0xFF && color2->g == 0x00 && color2->b == 0xFF))
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, GAME_LY + GAME_Y - y, color2);// trace le plafond
		else
			game_draw_pixel(game, game->sdl.text_buf, x + GAME_X, GAME_LY + GAME_Y - y, &((Uint8 *)(game->map.sky->pixels))[(sky) * 3 + (((GAME_LY) - y) * (game->map.sky->w) * 3)]);
		y++;
	}
}
