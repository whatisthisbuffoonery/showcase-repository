NAME := push_swap
BONUS_NAME := checker

CC := clang
CC_FLAGS := -Wall -Wextra -Werror
LIBFT_DIR := ../libft
LIBFT := libft
LIBFT_NAME := ft

SRC := main.c merge_sort.c turk.c duck.c lsd_radix.c msd_radix.c
BONUS_SRC := main_bonus.c utils_bonus.c
SHARED_SRC := op.c init.c
OBJ := $(SRC:.c=.o)
BONUS_OBJ := $(BONUS_SRC:.c=.o)
SHARED_OBJ := $(SHARED_SRC:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ) $(SHARED_OBJ) $(LIBFT_DIR)/$(LIBFT).a
	$(CC) $(CC_FLAGS) $(OBJ) $(SHARED_OBJ) -I $(LIBFT_DIR)/includes -L $(LIBFT_DIR) -l $(LIBFT_NAME) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(SHARED_OBJ) $(LIBFT_DIR)/$(LIBFT).a
	$(CC) $(CC_FLAGS) $(BONUS_OBJ) $(SHARED_OBJ) -I $(LIBFT_DIR)/includes -L $(LIBFT_DIR) -l $(LIBFT_NAME) -o $(BONUS_NAME)

#if using objects, emcc wants objects compiled out of emcc
#it will complain about libft not being a wasm thing, but it still runs
#-v mount /thing in docker to here/..
#-w cd back into here so the vars work
wasm: $(SRC) $(SHARED_SRC)
	docker run --rm \
	-v $(PWD)/..:/thing \
	-w /thing/$(notdir $(PWD)) \
	emscripten/emsdk emcc \
	$(SRC) $(SHARED_SRC) -I $(LIBFT_DIR)/includes -L $(LIBFT_DIR) -l $(LIBFT_NAME) -o $(NAME).wasm

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) -I $(LIBFT_DIR)/includes -c $< -o $@

$(BONUS_OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) -I $(LIBFT_DIR)/includes -c $< -o $@

$(SHARED_OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) -I $(LIBFT_DIR)/includes -c $< -o $@

$(LIBFT_DIR)/$(LIBFT).a:
	$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	rm -f $(OBJ) $(BONUS_OBJ) $(SHARED_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) $(NAME).wasm

re: fclean all

.PHONY: all clean fclean re bonus
