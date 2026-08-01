NAME := libft.a
CC := clang
CC_FLAGS := -Wall -Wextra -Werror -c -g
AR := ar
AR_FLAGS := rcs
INCLUDE_DIR := includes
OBJ_DIR := obj
GNL_DIR := gnl
FT_DIR := ft
PRINTF_DIR := printf
DEFINES := -DFT_LIST -DFT_GNL -DFT_PRINTF

FT_SRC := ft_atoi.c ft_atoi_ind.c ft_atohu_ind.c ft_bzero.c ft_calloc.c ht_init.c \
min2.c max2.c ft_abs.c \
ft_swap.c ft_swapf.c \
ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isquote.c ft_ishex.c ft_isspace.c \
ft_itoa.c ft_ftoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
ft_putnbr.c ft_putstr.c ft_putchar.c \
ft_strchr.c ft_strdup.c ft_strndup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strcmp.c \
ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
ft_ptrlen.c \
parsed_argsplit.c malloc_cond.c

LST_SRC := ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
ft_lstiter_chk.c ft_lstnew_chk.c

GNL_SRC := get_next_line_bonus.c get_next_line_utils_bonus.c get_next_line.c get_next_line_utils.c

PRINTF_SRC := ft_printf.c arg.c process.c token.c token_call.c q_func.c arg_help.c \
tabler_bonus.c type_bus_bonus.c handle_flag_bonus.c

FT_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(FT_SRC))

LST_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(LST_SRC))

GNL_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(GNL_SRC))

PRINTF_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(PRINTF_SRC))

OBJ := $(FT_OBJ) $(GNL_OBJ) $(PRINTF_OBJ) $(LST_OBJ)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(NAME): $(OBJ)
	$(AR) $(AR_FLAGS) $@ $^
	echo "\ntodo: remove some other static helpers\n\nDone"

$(FT_OBJ): $(OBJ_DIR)/%.o: $(FT_DIR)/%.c
	$(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) $< -o $@

$(LST_OBJ): $(OBJ_DIR)/%.o: $(FT_DIR)/%.c
	$(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) $< -o $@

$(GNL_OBJ): $(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) $< -o $@

$(PRINTF_OBJ): $(OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c
	$(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
