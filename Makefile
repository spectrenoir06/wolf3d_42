# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 10:11:24 by adoussau          #+#    #+#              #
#    Updated: 2014/11/28 15:13:43 by adoussau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STATIC_EXE	= wolf3d
DEBUG_EXE	= wolf3d_debug

SRC		=	main.c

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)

endif
ifeq ($(UNAME_S),Darwin)

endif

STATIC_OBJ	= $(patsubst %.c,$(STATIC_DIR)/%.o,$(SRC))
DEBUG_OBJ	= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))

HEAD_DIR	= includes
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
LIBFT_HEAD	= libft/includes/

CC			= gcc
FLAGS		= -Wall -Wextra -Werror
NORMINETTE	= ~/project/colorminette/colorminette
SDL			= -F framework -framework SDL2

$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR))

all: $(STATIC_EXE)

debug: $(DEBUG_EXE)

$(DEBUG_EXE): $(DEBUG_OBJ)
	$(CC) -I $(HEAD_DIR) -o $(DEBUG_EXE) $(DEBUG_OBJ) $(SDL) $(FLAGS) -g

$(STATIC_EXE): $(STATIC_OBJ)
	$(CC) -O3 -I $(HEAD_DIR) -o $@ $(STATIC_OBJ) $(SDL) $(FLAGS)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -O3 -I $(HEAD_DIR) -o $@ -c $< $(SDL) $(FLAGS)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(HEAD_DIR) -o $@ -c $< $(SDL) $(FLAGS) -g

.PHONY: clean fclean re debug norme

clean:
	rm -f $(STATIC_OBJ) $(DEBUG_OBJ)

fclean: clean
	rm -f $(STATIC_EXE) $(DEBUG_EXE)

norme: normeLibft
	$(NORMINETTE) $(SRC_DIR)/ $(HEAD_DIR)/

re: fclean
	make
