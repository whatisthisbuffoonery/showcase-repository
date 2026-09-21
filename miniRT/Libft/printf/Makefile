# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 21:29:55 by achew             #+#    #+#              #
#    Updated: 2026/01/31 18:53:02 by achew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I .

SRC = ft_printf.c \
	  is_fmt.c \
	  init_arg.c \
	  print_data.c \
	  ft_putchar.c \
	  ft_putstr.c \
	  ft_putnbr.c \
	  putnbr_u.c \
	  putptr.c \
	  puthex.c \
	  ft_atoi.c \
	  add_zero.c \
	  ft_memset.c \
	  ft_calloc.c

OBJ = $(SRC:.c=.o)

HDR = ft_printf.h

OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = libftprintf.a

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
