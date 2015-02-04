# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 10:11:24 by adoussau          #+#    #+#              #
#    Updated: 2015/01/26 23:43:03 by eteyssed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STATIC_EXE	= wolf3d
DEBUG_EXE	= wolf3d_debug

SRC		=	main.c		\
			game.c		\
			player.c	\
			vect.c		\
			map.c		\
			sound.c		\
			hud.c		\
			weapon.c	\
			sprites.c

##HEADFILES = wolf3d.h

HEAD_DIR	= includes
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
C_HEAD_DIR	= debug

LIBFT_STATIC= libft/libft.a
LIBFT_DEBUG	= libft/libft_debug.a
LIBFT_HEAD	= libft/includes/

STATIC_OBJ	= $(patsubst %.c,$(STATIC_DIR)/%.o,$(SRC))
DEBUG_OBJ	= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))
##HEADER_OBJ	= $(patsubst %.h,$(HEAD_DIR)/%.h.gch,$(HEADFILES))

CC			= gcc
FLAGS		=  -Wall -Wextra ##-Werror
NORMINETTE	= ~/project/colorminette/colorminette

UNAME_S := $(shell uname -s)

NAME := $(shell whoami)

ifeq ($(UNAME_S),Linux)
	SDL	= -lSDL2 -lm -lSDL_mixer
endif

ifeq ($(UNAME_S),Darwin)
	SDL	= -F ~/Library/Frameworks -I ~/Library/Frameworks/SDL2.framework/Headers/ -framework SDL2 -I ~/Library/Frameworks/SDL2_mixer.framework/Headers -framework SDL2_mixer
endif

$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR))

all: $(STATIC_EXE)
	@echo "je suis Charlie (realease)"
debug: $(DEBUG_EXE)
	@echo "je suis Charlie (debug)"
$(DEBUG_EXE): $(DEBUG_OBJ) $(LIBFT_DEBUG)
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $(DEBUG_EXE) $(DEBUG_OBJ) $(LIBFT_DEBUG) $(SDL) $(FLAGS) -g

$(STATIC_EXE): $(STATIC_OBJ) $(LIBFT_STATIC)
	$(CC) -O4 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(STATIC_OBJ) $(LIBFT_STATIC) $(SDL) $(FLAGS)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -O4 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(SDL) $(FLAGS)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(SDL) $(FLAGS) -g

$(LIBFT_STATIC):
	make -C libft/ libft.a

$(LIBFT_DEBUG):
	make -C libft/ libft_debug.a

##$(HEAD_DIR))/%.h.gch: $(HEAD_DIR))/%.h
##	$(CC) -I $(HEAD_DIR) -o $@ -c $<

.PHONY: clean fclean re debug norme

clean:
	rm -f $(STATIC_OBJ) $(DEBUG_OBJ)
	make -C libft clean

fclean: clean
	rm -f $(STATIC_EXE) $(DEBUG_EXE)
	make -C libft fclean

norme:
	$(NORMINETTE) $(SRC_DIR)/ $(HEAD_DIR)/
	make -C libft norme

re: fclean
	make
