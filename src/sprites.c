
#include "wolf3d.h"

inline int		sprite_compare(void *entity1, void *entity2)
{
	return (((t_entity *)entity2)->dist - ((t_entity *)entity1)->dist);
}

void	game_draw_sprites_init(t_drsprite *sprt, t_game *game)
{
	sprt->spritex = game->map.entity_ptr[sprt->x]->pos.x - game->player.pos.x;
	sprt->spritey = game->map.entity_ptr[sprt->x]->pos.y - game->player.pos.y;
	sprt->invdet = 1.0 / (game->player.plane.x * game->player.dir.y -
	game->player.dir.x * game->player.plane.y);
	sprt->transformX = sprt->invdet * (game->player.dir.y * sprt->spritex -
	game->player.dir.x * sprt->spritey);
	sprt->transformY = sprt->invdet * (-game->player.plane.y * sprt->spritex +
	game->player.plane.x * sprt->spritey);
	sprt->spriteScreenX = (int)(((GAME_LX) / 2.0) *
	(1 + sprt->transformX / sprt->transformY));
	sprt->spriteheight = abs((int)((GAME_LY) / sprt->transformY));
	sprt->drawStartY = -sprt->spriteheight / 2.0 + (GAME_LY) / 2.0;
	if (sprt->drawStartY < 0)
		sprt->drawStartY = 0;
	sprt->drawEndY = sprt->spriteheight / 2.0 + (GAME_LY) / 2.0;
	if (sprt->drawEndY >= (GAME_LY))
		sprt->drawEndY = (GAME_LY) - 1;
	sprt->spriteWidth = abs((int)((GAME_LY) / sprt->transformY));
	sprt->drawStartX = -sprt->spriteWidth / 2.0 + sprt->spriteScreenX;
	if (sprt->drawStartX < 0)
		sprt->drawStartX = 0;
	sprt->drawEndX = sprt->spriteWidth / 2.0 + sprt->spriteScreenX;
	if (sprt->drawEndX >= (GAME_LX))
		sprt->drawEndX = (GAME_LX) - 1;
	sprt->stripe = sprt->drawStartX - 1;
}

void	game_draw_sprites_draw(t_drsprite *sprt, t_game *game)
{
	sprt->d = sprt->y - (GAME_LY) / 2.0 + sprt->spriteheight / 2.0;
	sprt->texY = ((sprt->d * 512) / sprt->spriteheight);
	sprt->pos.x = game->player.pos.x - game->map.entity_ptr[sprt->x]->pos.x;
	sprt->pos.y = game->player.pos.y - game->map.entity_ptr[sprt->x]->pos.y;
	if (game->map.sprite[game->map.entity_ptr[sprt->x]->texture].frames == 8)
	{
		sprt->angle = atan2(sprt->pos.y, sprt->pos.x) -
		atan2(game->map.entity_ptr[sprt->x]->dir.y,
		game->map.entity_ptr[sprt->x]->dir.x) + M_PI_4 / 2;
		if (sprt->angle < 0)
			sprt->angle += 2 * M_PI;
		sprt->i = ((sprt->angle) / (M_PI * 2.0) * 8.0);
		sprt->i = sprt->i > 7 ? 7 : sprt->i;
		sprt->i = sprt->i < 0 ? 0 : sprt->i;
	}
	else
		sprt->i = 0;
	sprt->color = (t_color *) &((Uint8*)(game->map.sprite[game->map.entity_ptr
	[sprt->x]->texture].tex->pixels))[(int)sprt->texX * 3 + (sprt->texY * 3 *
	game->map.sprite[game->map.entity_ptr[sprt->x]->texture].tex->w) +
	(sprt->i * 3 * TEX_SIZE)];
	if (!(sprt->color->r == 0xFF && sprt->color->g == 0x00 &&
		sprt->color->b == 0xFF))
		game_draw_pixel(game, game->sdl.text_buf, GAME_X + GAME_LX -
		sprt->stripe, GAME_Y + sprt->y, sprt->color);
}

void	game_sort_sprites(t_drsprite *sprt, t_game *game)
{
	sprt->x = -1;
	while (++sprt->x < game->map.nb_entity)
		game->map.entity[sprt->x].dist = ((game->player.pos.x - game->map.entity
		[sprt->x].pos.x) * (game->player.pos.x - game->map.entity[sprt->x].pos.x)
		+ (game->player.pos.y - game->map.entity[sprt->x].pos.y) *
		(game->player.pos.y - game->map.entity[sprt->x].pos.y));
	ft_sort_qck((void **)game->map.entity_ptr,
	game->map.nb_entity, sprite_compare);
}

void	game_draw_sprites(t_game *game)
{
	t_drsprite	sprt;

	game_sort_sprites(&sprt, game);
	sprt.x = -1;
	while (++sprt.x < game->map.nb_entity)
	{
		game_draw_sprites_init(&sprt, game);
		while (++sprt.stripe <= sprt.drawEndX)
		{
			sprt.texX = (int)(256 * (sprt.stripe - (-sprt.spriteWidth / 2 +
			sprt.spriteScreenX)) * 512 / sprt.spriteWidth / 256);
			if (sprt.transformY > 0 && sprt.stripe > 0 && sprt.stripe <
				(GAME_LX) && sprt.transformY < game->Zbuffer[sprt.stripe])
			{
				sprt.y = sprt.drawStartY - 1;
				while (++sprt.y < sprt.drawEndY)
					game_draw_sprites_draw(&sprt, game);
			}
		}
	}
}
