
### --- COLORS --- ###

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
PURPLE	= '\033[1;35m'
YELLOW	= '\033[1;33m'
WHITE	= '\033[0;37m'
BLUE	= '\033[1;34m'

NAME = cub3D

LIB_GNL = -I$(LIBGNL_PATH) -L$(LIBGNL_PATH) -lgnl
LIB_FT = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft

SRCS_PATH = src/
INCS_PATH = inc/
BIN_PATH = bin/
LIBGNL_PATH = gnl/
LIBFT_PATH = libft/


SRCS = main.c \
		read_file.c \
		matrix.c \
		player_function.c \
		images.c \
		window.c \
		key_pressed.c \
		movement.c \
		exit_game.c \
		new_raycast.c \
		walls.c
# 		raycast.c 

OBJS = $(SRCS:%.c=bin/%.o)

CC = gcc
CFLAGS =-Wall -Werror -Wextra -g3 -O0
RM = rm -f


ifeq ($(shell uname), Linux)
	#LIBMLX_PATH = ./mlx_linux/
	OBJ_COMPIL = -I/usr/include -Imlx_linux -O0 -c $< -o $@
	LIB_FLAGS = -L/usr/lib -lXext -lX11 -lm -lz
	LIB_COMPIL = -Lmlx_linux -lmlx $(LIB_FLAGS) $(LIB_GNL) $(LIB_FT)
	SO = Linux
else
	OBJ_COMPIL = -Imlx -c $< -o $@
	LIB_COMPIL = -lmlx -framework OpenGL -framework AppKit $(LIB_FLAGS) $(LIB_GNL) $(LIB_FT) -o $(NAME)
endif


###		RULES		###

all: $(NAME)

bin/%.o: src/%.c
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(OBJ_COMPIL)

$(NAME): $(OBJS)
	@echo $(PURPLE)"[Creating libgnl]"$(BLUE)
	@$(MAKE) -C $(LIBGNL_PATH) --silent
	@echo $(PURPLE)"[Creating libft]"$(BLUE)
	@$(MAKE) -C $(LIBFT_PATH) --silent
	@echo $(PURPLE)"[Creating cub3D]"$(BLUE)
	@$(CC) -o $(NAME) $(OBJS) $(LIB_COMPIL) #-fsanitize=address
	@echo $(GREEN)"$(NAME): ready to be executed"$(WHITE)

clean:
	@$(RM) $(OBJS)
	@rm -rf bin/
	@$(MAKE) -C $(LIBGNL_PATH) clean --silent
	@$(MAKE) -C $(LIBFT_PATH) clean --silent
	@echo $(RED)"[Object Files Deleted]"$(WHITE)

fclean: clean
	@$(RM) $(NAME)
	@echo $(RED)"[Executable File Deleted]"$(WHITE)
	@$(MAKE) -C $(LIBGNL_PATH) fclean --silent
	@$(MAKE) -C $(LIBFT_PATH) fclean --silent

re: fclean $(NAME)

run: $(NAME)
	@./cub3d maps/24x14.cub

.PHONY: all clean fclean re
