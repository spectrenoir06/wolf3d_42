/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:55:44 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/13 16:55:46 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include <stdio.h>

static void				ft_initwin(void)
{
	SDL_Window			*win;
	SDL_Event			event;
	SDL_Texture			*tex;
	SDL_Renderer		*rd;
	Uint32				*texturebuf;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(500, 500, SDL_WINDOW_SHOWN, &win, &rd);
	tex = SDL_CreateTexture(rd, SDL_PIXELFORMAT_RGBA8888,
							SDL_TEXTUREACCESS_STREAMING, 500, 500);
	if (win == NULL)
		printf("Wolf3D: Error => windows cant load\n");
	while (42)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_DestroyWindow(win);
			SDL_Quit();
			exit(0);
		}
		SDL_UpdateTexture(tex, NULL, texturebuf, 500 * sizeof(Uint32));
		SDL_RenderCopy(rd, tex, NULL, NULL);
		SDL_RenderPresent(rd);
	}
}

int						main(void)
{
	ft_initwin();
	return (0);
}
