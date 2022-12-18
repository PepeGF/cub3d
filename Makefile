
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
LIB_MLX = -I$(MLX_PATH) -LMLX42/ -lmlx42

SRCS_PATH = src/
INCS_PATH = inc/
BIN_PATH = bin/
LIBGNL_PATH = gnl/
LIBFT_PATH = libft/
MLX_PATH = MLX42/include/MLX42/


SRCS = main.c read_file.c matrix.c

OBJS = $(SRCS:%.c=bin/%.o)

CC = gcc
CFLAGS =-Wall -Werror -Wextra -g -O0
# RM = rm -f se puede quitar xq es una variable automática de make

###		RULES		###

all: $(NAME)

bin/%.o: src/%.c
	@mkdir -p bin
	@$(CC) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

$(NAME): $(OBJS)
	@echo $(PURPLE)"[Creating libgnl]"$(BLUE)
	@$(MAKE) -C $(LIBGNL_PATH) --silent
	@echo $(PURPLE)"[Creating libft]"$(BLUE)
	@$(MAKE) -C $(LIBFT_PATH) --silent
	@echo $(PURPLE)"[Creating libmlx42]"$(BLUE)
	@$(MAKE) -C MLX42/ --silent
	@echo $(PURPLE)"[Creating cub3D]"$(BLUE)
	@$(CC) -o $(NAME) $(OBJS) $(LIB_MLX) -lglfw $(LIB_FT) $(LIB_GNL) -fsanitize=address
	@echo $(GREEN)"$(NAME): ready to be executed"$(WHITE)

clean:
	@$(RM) $(OBJS)
	@rm -rf bin/
	@$(MAKE) -C $(LIBGNL_PATH) clean --silent
	@$(MAKE) -C $(LIBFT_PATH) clean --silent
	@echo $(RED)"[Object Files Deleted]"$(WHITE)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C MLX42/ fclean --silent
	@echo $(RED)"[Executable File Deleted]"$(WHITE)
	@$(MAKE) -C $(LIBGNL_PATH) fclean --silent
	@$(MAKE) -C $(LIBFT_PATH) fclean --silent

re: fclean 
	@$(MAKE)

run: $(NAME)
	@./cub3d maps/37x14.cub

.PHONY: all clean fclean re
