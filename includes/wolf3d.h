/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 19:13:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/13 19:13:50 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>
# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "libft.h"

# ifdef __APPLE__
#  include "SDL.h"
#  include "SDL_mixer.h"
#  include "SDL_net.h"
# elif __linux
#  include <SDL2/SDL.h>
#  include <SDL/SDL_mixer.h>
#  include <SDL/SDL_net.h>
# endif

# define WIN_LX 1600	//
# define WIN_LY 900		//
# define GAME_X1 40		// decalage X
# define GAME_Y1 20		// decalage Y

# define GAME_LX 1520
# define GAME_LY 660

# define GAME_X2 (GAME_X1 + GAME_LX)
# define GAME_Y2 (GAME_Y1 + GAME_LY)

# define TEX_SIZE 512
# define SINT16_MAX 32767
# define SINT16_MIN -32768
# define DSINT16_MAX 32767

# define WALL 0x000000
# define FLOOR 0x999999
# define PLAYER 0x0099FF
# define FACE 0xFF9900

# include "struct.h"
# include "header.h"

#endif
