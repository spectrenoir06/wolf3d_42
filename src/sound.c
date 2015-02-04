/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteyssed <eteyssed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 02:22:25 by eteyssed          #+#    #+#             */
/*   Updated: 2015/01/29 17:33:50 by eteyssed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	game_init_sdl_mixer(t_sounds *sounds)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,
			MIX_DEFAULT_CHANNELS, 1024) == -1)
		ft_putstr("Error : Couldn't initialize SDL_mixer.");
	Mix_AllocateChannels(8);
	sounds->music = Mix_LoadMUS("modes/1/maps/1/music/level.midi");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
	Mix_PlayMusic(sounds->music, 1);
	Mix_SetMusicPosition(3.0);
	sounds_init(sounds);
}

void	sounds_init(t_sounds *sounds)
{
	sounds->pas = Mix_LoadWAV("modes/1/maps/1/sfx/run.wav");
	Mix_VolumeChunk(sounds->pas, MIX_MAX_VOLUME / 2);
	sounds->son1 = Mix_LoadWAV("modes/1/maps/1/sfx/fear.wav");
	Mix_VolumeChunk(sounds->son1, MIX_MAX_VOLUME / 2);
	sounds->son2 = Mix_LoadWAV("modes/1/maps/1/sfx/shoot2.wav");
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
