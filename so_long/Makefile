SRCS	= gnl/get_next_line_utils.c gnl/get_next_line.c \
			main.c leaks.c \
			read_file.c free_variables.c matrix.c \
			check_matrix.c check_matrix_cont.c check_matrix_values.c utils.c \
			#make_movement.c \
			#key_pressed.c first_window_images.c replace_imgs.c player_function.c \
			print_steps.c  raycasting.c
# go_down.c go_up.c go_right.c go_left.c exit_game.c 

LIBFT_PATH = libft/

OBJS	= $(SRCS:.c=.o)

NAME	= so_long

CFLAGS	= -Wall -Werror -Wextra -g3 -O0 #--analyze

GCC	= gcc

RM	= rm -f

all:		$(NAME)

.c.o:
	$(GCC) $(CFLAGS)  -c $< -o $@ -I$(LIBFT_PATH)

$(NAME):	$(OBJS)
	make -C $(LIBFT_PATH) --silent
	$(CC) -o $(NAME) $(OBJS) -o $(NAME) -I./libft -L./libft -lft 

clean:		
	$(RM) $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean:		clean
		$(RM) $(NAME)
		make -C $(LIBFT_PATH) fclean 

re:		fclean all

.PHONY:		all clean fclean re 