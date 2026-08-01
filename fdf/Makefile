MLX_DIR := minilibx-linux
LIBFT_DIR := ../libft
LIBFT := $(LIBFT_DIR)/libft.a
INCLUDES := -I$(MLX_DIR) -I$(LIBFT_DIR)/includes
LIBS := -lm -lXext -lX11 -lmlx -lft -L$(MLX_DIR) -L$(LIBFT_DIR) -L/usr/lib/X11
CC := clang
CC_FLAGS := -Wall -Wextra -Werror -g
SRC := main.c view.c frame.c ras.c xiaoxiao.c pt.c bresenham.c usage.c
SRC_MAND := loop_mand.c
SRC_BONUS := loop_bonus.c
OBJ := $(SRC:.c=.o)
OBJ_MAND := $(SRC_MAND:.c=.o)
OBJ_BONUS := $(SRC_BONUS:.c=.o)
MLX := $(MLX_DIR)/libmlx.a
NAME := fdf
FULL := fdf_bonus

all: $(NAME)

bonus: $(FULL)

$(NAME): $(OBJ) $(OBJ_MAND) $(LIBFT) $(MLX)
	$(CC) $(CC_FLAGS) $(OBJ) $(OBJ_MAND) $(LIBS) $(INCLUDES) -o $(NAME)

$(FULL): $(OBJ) $(OBJ_BONUS) $(LIBFT) $(MLX)
	$(CC) $(CC_FLAGS) $(OBJ) $(OBJ_BONUS) $(LIBS) $(INCLUDES) -o $(FULL)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(MLX):
	$(MAKE) -C $(MLX_DIR) all

$(OBJ): %.o: %.c h_mlx.h
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_MAND): %.o: %.c h_mlx.h
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_BONUS): %.o: %.c h_mlx.h
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJ_MAND) $(OBJ_BONUS)

fclean: clean
	rm -rf $(NAME) $(FULL)

re: fclean all

.PHONY: all clean fclean re bonus
