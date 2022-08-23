#include "../gnl/get_next_line.h"
#include "../libft/libft.h"

typedef struct s_board {
	int		col;
	int		row;
	char	type;
	int		is_border;
	int		jug;
	int		coll;
	int		end;
}	t_board;