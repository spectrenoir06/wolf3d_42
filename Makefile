# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 10:11:24 by adoussau          #+#    #+#              #
#*   Updated: 2015/02/05 22:37:42 by adoussau         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

STATIC_EXE	= wolf3d
DEBUG_EXE	= wolf3d_debug
GPROF_EXE	= wolf3d_gprof

SRC		=	main.c		\
			game.c		\
			player.c	\
			vect.c		\
			map.c		\
			sound.c		\
			hud.c		\
			weapon.c	\
			sprites.c	\
			joystick.c	\
			keyboard.c	\
			render.c	\
			pixel.c		\
			map_dlc.c	\
			multi.c		\
			caster.c

##HEADFILES = wolf3d.h

HEAD_DIR	= includes
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
GPROF_DIR	= gprof
C_HEAD_DIR	= debug

LIBFT_STATIC= libft/libft.a
LIBFT_DEBUG	= libft/libft_debug.a
LIBFT_HEAD	= libft/includes/

STATIC_OBJ	= $(patsubst %.c,$(STATIC_DIR)/%.o,$(SRC))
DEBUG_OBJ	= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))
GPROF_OBJ	= $(patsubst %.c,$(GPROF_DIR)/%.o,$(SRC))


CC		= gcc
NORMINETTE	= ~/project/colorminette/colorminette
OPTI		= O3

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	SDL	= -lm -lSDL2 -lSDL_mixer -lSDL_net
	FLAGS	= -Wall -Wextra -Wno-unused-result
endif

ifeq ($(UNAME_S),Darwin)
	SDL2		= -framework SDL2
	SDL2_MIXER	= -framework SDL2_mixer
	SDL2_NET	= -framework SDL2_net

	SDL2_HEADER			= -I ~/Library/Frameworks/SDL2.framework/Headers/
	SDL2_HEADER_MIXER	= -I ~/Library/Frameworks/SDL2_mixer.framework/Headers/
	SDL2_HEADER_NET		= -I ~/Library/Frameworks/SDL2_net.framework/Headers/

	SDL			= -F ~/Library/Frameworks $(SDL2) $(SDL2_MIXER) $(SDL2_NET)
	SDL_HEADER	= -F ~/Library/Frameworks $(SDL2_HEADER) $(SDL2_HEADER_MIXER) $(SDL2_HEADER_NET)
	FLAGS		= -Wall -Wextra
endif



$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR) $(GPROF_DIR))

all: $(STATIC_EXE)
	@echo "Compilation terminee. (realease)"

debug: $(DEBUG_EXE)
	@echo "Compilation terminee. (debug)"

gprof: $(GPROF_EXE)
	@echo "Compilation terminee. (gprof)"

###############################################################################################################

$(DEBUG_EXE): $(DEBUG_OBJ) $(LIBFT_DEBUG)
	$(CC) -O0 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $(DEBUG_EXE) $(DEBUG_OBJ) $(LIBFT_DEBUG) $(SDL) $(FLAGS) -g

$(STATIC_EXE): $(STATIC_OBJ) $(LIBFT_STATIC)
	$(CC) -$(OPTI) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(STATIC_OBJ) $(LIBFT_STATIC) $(SDL) $(FLAGS)

$(GPROF_EXE): $(GPROF_OBJ) $(LIBFT_STATIC)
	$(CC) -$(OPTI) -pg -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(GPROF_OBJ) $(LIBFT_STATIC) $(SDL) $(FLAGS)

################################################################################################################

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -$(OPTI) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(SDL_HEADER) -c $< $(FLAGS)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -O0 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(SDL_HEADER) -c $< $(FLAGS) -g

$(GPROF_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -$(OPTI) -pg -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(SDL_HEADER) -c $< $(FLAGS) -g

################################################################################################################

$(LIBFT_STATIC):
	make -C libft/ libft.a

$(LIBFT_DEBUG):
	make -C libft/ libft_debug.a

.PHONY: clean fclean re debug normem sdl_install gprof

clean:
	rm -f $(STATIC_OBJ) $(DEBUG_OBJ) $(GPROF_OBJ)
	make -C libft clean

fclean: clean
	rm -f $(STATIC_EXE) $(DEBUG_EXE) $(GPROF_EXE)
	make -C libft fclean

norme:
	$(NORMINETTE) $(SRC_DIR)/ $(HEAD_DIR)/
	make -C libft norme

sdl_install:
	curl https://dl.dropboxusercontent.com/u/22561204/SDL/Archive.zip > /tmp/Archive.zip
	unzip -o /tmp/Archive.zip -d ~/Library/Frameworks/

re: fclean
	make
