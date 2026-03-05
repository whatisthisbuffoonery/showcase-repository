CC := clang
CC_FLAGS := -Wall -Wextra -Werror -c -g

AR := ar
AR_FLAGS := rcs

NAME := libftprintf.a
FULL := full.a

LIBFT_DIR := ../libft
LIBFT_LIB := libft

SRC := ft_printf.c arg.c process.c token.c token_call.c \
	   q_func.c arg_help.c

SRC_MAND := tabler_mand.c type_bus_mand.c handle_flag_mand.c

SRC_BONUS := tabler_bonus.c type_bus_bonus.c handle_flag_bonus.c

OBJ := $(SRC:.c=.o)

OBJ_MAND := $(SRC_MAND:.c=.o)

OBJ_BONUS := $(SRC_BONUS:.c=.o)

debug:
	$(MAKE) -C $(LIBFT_DIR) all
	$(CC) $(CC_FLAGS) main.c $(SRC) $(SRC_BONUS) $(LIBFT_DIR)/$(LIBFT_LIB).a

all: bonus

bonus: $(FULL)

$(NAME): $(OBJ) $(OBJ_MAND)
	$(MAKE) -C $(LIBFT_DIR) all
	cp -r $(LIBFT_DIR)/$(LIBFT_LIB).a ./$(NAME)
	$(AR) $(AR_FLAGS) $(NAME) $(OBJ) $(OBJ_MAND)

$(FULL): $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR) all
	cp -r $(LIBFT_DIR)/$(LIBFT_LIB).a ./$(FULL)
	$(AR) $(AR_FLAGS) $(FULL) $(OBJ) $(OBJ_BONUS)
	cp -r $(FULL) $(NAME)

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) $< -o $@

$(OBJ_MAND): %.o: %.c
	$(CC) $(CC_FLAGS) $< -o $@

$(OBJ_BONUS): %.o: %.c
	$(CC) $(CC_FLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_MAND) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(FULL)

re: fclean all

.PHONY: all clean fclean re bonus
