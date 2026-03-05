CC := clang
CC_FLAGS := -Wall -Wextra -Werror -g
NAME := pipex
FULL := full
LIBFT_DIR := ../libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_NAME := ft

SRC := child.c cmd.c fork.c main.c open.c utils.c cpid.c cleanup.c err.c

MAND_OBJ := heredoc.o

BONUS_OBJ := heredoc_bonus.o

OBJ := $(SRC:.c=.o)

all: $(NAME)

bonus: $(FULL)

$(NAME): $(OBJ) $(MAND_OBJ) $(LIBFT)
	$(CC) $(CC_FLAGS) $(OBJ) $(MAND_OBJ) $(LIBFT) -I $(LIBFT_DIR)/includes -o $(NAME)

$(FULL): $(OBJ) $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CC_FLAGS) $(OBJ) $(BONUS_OBJ) $(LIBFT) -I $(LIBFT_DIR)/includes -o $(FULL)
	cp -p $(FULL) $(NAME)

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) -c $< -I $(LIBFT_DIR)/includes -o $@

$(MAND_OBJ): heredoc.c
	$(CC) $(CC_FLAGS) -c $< -I $(LIBFT_DIR)/includes -o $@

$(BONUS_OBJ): heredoc_bonus.c
	$(CC) $(CC_FLAGS) -c $< -I $(LIBFT_DIR)/includes -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

clean:
	rm -rf $(OBJ) $(MAND_OBJ) $(BONUS_OBJ)

fclean: clean
	rm -rf $(NAME) $(FULL)

re: fclean all

.PHONY: all clean fclean re bonus
