# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 21:29:55 by achew             #+#    #+#              #
#    Updated: 2026/08/20 16:15:08 by achew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME        := miniRT
NAME_BONUS  := miniRT_bonus

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g -O0

LIBFT_DIR   := ./Libft
MLX_DIR     := ./Minilibx/minilibx-linux

INCLUDES    := -Iinclude -I$(LIBFT_DIR)/libft -I$(LIBFT_DIR)/gnl -I$(LIBFT_DIR)/printf -I$(MLX_DIR)

LIBFT_LIB   := $(LIBFT_DIR)/libft/libft.a
GNL_LIB     := $(LIBFT_DIR)/gnl/libftgnl.a
PRINTF_LIB  := $(LIBFT_DIR)/printf/libftprintf.a
MLX_LIB     := $(MLX_DIR)/libmlx_Linux.a

LIBS        := $(LIBFT_LIB) $(GNL_LIB) $(PRINTF_LIB) $(MLX_LIB)
SYS_LIBS    := -lXext -lX11 -lm

HDR 	    := include/h_minirt.h
HDR_BONUS   := include/h_minirt_bonus.h

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRC_DIR         := src/

SRC_BASE        := main.c \
                   rt_init.c \
                   fd_ops.c \
                   exit.c \
                   cleanup.c \
                   valid_ext.c \
                   vec3.c \
                   tokenize.c \
                   token_utils.c \
                   parse_utils.c \
                   parse_dispatch.c \
                   parse_ambient.c \
                   parse_camera.c \
                   parse_light.c \
                   parse_sphere.c \
                   parse_plane.c \
                   parse_cylinder.c \
				   parse_cone.c \
                   object_list.c \
                   light_list.c \
                   debug_scene.c \
				   discriminant.c \
				   discriminant_help.c \
				   cap.c \
				   normal.c \
				   direction.c \
				   color.c \
				   buf_edit.c \
				   quaternion.c \
				   loop.c \
				   ft_strcmp.c \
				   draw_frame.c \
				   dummy_phong.c

MAND_COMPONENT  := mand_or_bonus.c \

BONUS_COMPONENT := minirt_bonus1.c \

SRC       := $(SRC_BASE) $(MAND_COMPONENT)

SRC_BONUS := $(SRC_BASE) $(BONUS_COMPONENT)

# **************************************************************************** #
#                                   OBJECTS                                    #
# **************************************************************************** #

OBJ_DIR     := obj/

OBJ         := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_BONUS   := $(addprefix $(OBJ_DIR), $(SRC_BONUS:.c=.o))

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: mlx libft $(NAME)

bruh: objclean $(NAME)

bonus: mlx libft $(NAME_BONUS)

# -------------------- Submodules --------------------

.PHONY: mlx libft

libft:
	$(MAKE) -C $(LIBFT_DIR) bonus

mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		mkdir -p Minilibx; \
		wget --no-check-certificate https://cdn.intra.42.fr/document/document/51700/minilibx-linux.tgz -P Minilibx; \
		cd Minilibx && tar -xzf minilibx-linux.tgz; \
	fi
	$(MAKE) -C $(MLX_DIR)

$(LIBS): ;

# -------------------- Main binary --------------------

ifneq ($(filter bonus re_bonus,$(MAKECMDGOALS)),)
LINK_OBJ = $(OBJ_BONUS)
LINK_HDR = $(HDR_BONUS)
else
LINK_OBJ = $(OBJ)
LINK_HDR = $(HDR)
endif

$(NAME): $(LINK_OBJ) $(LINK_HDR) 
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJ) $(LIBS) $(SYS_LIBS) -o $(NAME)

$(NAME_BONUS): $(LINK_OBJ) $(LINK_HDR) $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJ) $(LIBS) $(SYS_LIBS) -o $(NAME_BONUS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LINK_HDR) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# **************************************************************************** #
#                                   CLEAN                                      #
# **************************************************************************** #

objclean:
	rm -rf $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf Minilibx

re: fclean all
re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus
