/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 02:22:25 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/29 17:33:50 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	game_init_sdl_mixer(t_sounds *sounds, char *path)
{
	char	buff[256];

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,
			MIX_DEFAULT_CHANNELS, 1024) == -1)
		ft_putstr("Error : Couldn't initialize SDL_mixer.");
	Mix_AllocateChannels(8);
	ft_kebab(buff, path, "music/level.midi", NULL);
	sounds->music = Mix_LoadMUS(buff);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
	Mix_PlayMusic(sounds->music, 1);
	Mix_SetMusicPosition(3.0);
	sounds_init(sounds, path);
}

void	sounds_init(t_sounds *sounds, char *path)
{
	char	buff[256];

	ft_kebab(buff, path, "sfx/run.wav", NULL);
	sounds->pas = Mix_LoadWAV(buff);
	Mix_VolumeChunk(sounds->pas, MIX_MAX_VOLUME / 2);
	ft_kebab(buff, path, "sfx/fear.wav", NULL);
	sounds->son1 = Mix_LoadWAV(buff);
	Mix_VolumeChunk(sounds->son1, MIX_MAX_VOLUME / 2);
	ft_kebab(buff, path, "sfx/shoot2.wav", NULL);
	sounds->son2 = Mix_LoadWAV(buff);
	Mix_VolumeChunk(sounds->son2, MIX_MAX_VOLUME / 2);
}

void	sdl_mixer_quit(t_sounds *sounds)
{
	Mix_FreeMusic(sounds->music);
	Mix_FreeChunk(sounds->pas);
	Mix_FreeChunk(sounds->son1);
	Mix_FreeChunk(sounds->son2);
	Mix_CloseAudio();
}
