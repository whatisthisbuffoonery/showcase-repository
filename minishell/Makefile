# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 21:29:55 by achew             #+#    #+#              #
#    Updated: 2026/06/22 01:42:02 by dthoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME        := minishell 
BONUS_NAME  := minishell_bonus

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g -O0

LIBFT_DIR   := ../libft

LIBFT_LIB   := $(LIBFT_DIR)/libft.a

INCLUDES    := -I$(LIBFT_DIR)/includes -Iinclude
LIBS        := $(LIBFT_LIB) -lreadline -lhistory

HDR 		:= include/h_minishell.h
HDR_BONUS	:= $(HDR)

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #
SRC_DIR     := src/

SRC_BASE	:= main.c loop.c display.c buf_check.c err.c signal.c word.c update.c cleanup.c checker.c \
			ast_check.c ast_init.c ast_logic.c ast_redir.c \
			expand.c expand_utils.c expand_handlers.c field.c glob_utils.c \
			echo.c exit.c pwd.c export.c export_helpers.c unset.c env.c cd.c cd_utils.c cd_exit.c \
			argv.c path.c argv_empty.c argv_empty_utils.c redir.c heredoc.c envp.c exec.c arg_cleanup.c \
			child.c pipe_utils.c do_list.c exec_cleanup.c \
			env_init.c shnode_cleanup.c shnode_utils.c find.c \
			tok_init.c tok_utils.c

MAND_COMPONENT := tok_checker_mand.c ast_mand.c

BONUS_COMPONENT := tok_checker.c ast_extras.c

SRC := $(SRC_BASE) $(MAND_COMPONENT)

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

.PHONY: libft

all: libft $(NAME)

bonus: libft $(BONUS_NAME)

libft:
	$(MAKE) -C $(LIBFT_DIR)

$(LIBFT_LIB): ;

# -------------------- Main binary --------------------
ifneq ($(filter bonus re_bonus,$(MAKECMDGOALS)),)
LINK_OBJ = $(OBJ_BONUS)
LINK_HDR = $(HDR_BONUS)
else
LINK_OBJ = $(OBJ)
LINK_HDR = $(HDR)
endif

$(NAME): $(LINK_OBJ) $(LINK_HDR) $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJ) $(LIBS) -o $(NAME)

$(BONUS_NAME): $(LINK_OBJ) $(LINK_HDR) $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJ) $(LIBS) -o $(BONUS_NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LINK_HDR) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# **************************************************************************** #
#                                   CLEAN                                      #
# **************************************************************************** #

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus
