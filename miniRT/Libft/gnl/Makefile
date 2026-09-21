# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 21:29:55 by achew             #+#    #+#              #
#    Updated: 2026/02/01 14:30:39 by achew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I .

SRC = get_next_line.c \
	  get_next_line_utils.c \

HDR = get_next_line.h \

HDR_BONUS = get_next_line_bonus.h \

SRC_BONUS = get_next_line_bonus.c \
			get_next_line_utils_bonus.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = libftgnl.a

all: $(NAME)

bonus: $(NAME)

ifneq ($(filter bonus re_bonus,$(MAKECMDGOALS)),)
EXTRA_OBJ = $(OBJ_BONUS)
EXTRA_HDR = $(HDR_BONUS)
else
EXTRA_OBJ =
EXTRA_HDR =
endif

$(NAME): $(OBJ) $(EXTRA_OBJ)
	ar rcs $@ $?

%.o: %.c $(HDR) $(EXTRA_HDR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY: clean fclean re bonus re_bonus
