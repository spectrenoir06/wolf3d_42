/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
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
# elif __linux
#  include <SDL2/SDL.h>
#  include <SDL/SDL_mixer.h>
# endif

# define WIN_X 1600
# define WIN_Y 900
# define GAME_X 40
# define GAME_Y 20
# define GAME_LX 1520
# define GAME_LY 660
# define TEX_SIZE 512
# define SINT16_MAX 32767
# define SINT16_MIN -32768.0
# define DSINT16_MAX 32767.0

# define WALL 0x00FF00
# define FLOOR 0xFF0000
# define PLAYER 0x0000FF
# define FACE 0x0099FF

# include "struct.h"
# include "header.h"

#endif
