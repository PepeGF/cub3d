#include "../inc/cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == key_esc || keycode == key_space || keycode == key_q)
		exit_game(data);

	if (keycode == key_left || keycode == key_right)
		turn(data, keycode);

	if (keycode == key_w || keycode == key_s || keycode == key_up || keycode == key_down)
		front_back(data, keycode);
	
	if (keycode == key_a || keycode == key_d)
		side_move(data, keycode);
	return (0);
}