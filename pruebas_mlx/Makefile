NAME = wololo

SRCS = pruebas_mlx.c

OBJS = $(SRCS:%.c=%.o)

CC = gcc
CFLAGS =-Wall -Werror -Wextra -g -O0
RM = rm -f

LIBFT_PATH = ../libft/
LIB_FT = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft

OBJ_COMPIL = -Imlx -c $< -o $@
LIB_COMPIL = -lmlx -framework OpenGL -framework AppKit $(LIB_FLAGS) $(LIB_GNL) $(LIB_FT) -o $(NAME)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(OBJ_COMPIL)

$(NAME): $(OBJS)
	@echo $(PURPLE)"[Creating libft]"$(BLUE)
	@$(MAKE) -C $(LIBFT_PATH) --silent
	@echo "[Creating cub3D]"
	@$(CC) -o $(NAME) $(OBJS) $(LIB_COMPIL) -fsanitize=address
	@echo "$(NAME): ready to be executed"

clean:
	@$(RM) $(OBJS)
	@echo "[Object Files Deleted]"

fclean: clean
	@$(RM) $(NAME)
	@echo "[Executable File Deleted]"

re: fclean $(NAME)

.PHONY: all clean fclean re