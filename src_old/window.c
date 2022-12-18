#include "../inc/cub3d.h"

void	put_field(t_board **matrix, int row, int col, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < row)
	{
		j = 0;
		while (j < col)
		{
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->field,
				(matrix[i][j].col * data->px), (matrix[i][j].row * data->px));
			j++;
		}
	}
}

void	replace_field(t_board **matrix, int row, int col, t_data *data)
{
	replace_border_img(matrix, row, col, data);
	replace_player_img(matrix, row, col, data);
}

void	draw_full_map(t_board **matrix, int row, int col, t_data *data)
{
	put_field(matrix, row, col, data);
	replace_field(matrix, row, col, data);
}

void	replace_border_img(t_board **matrix, int row, int col, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < row)
	{
		j = 0;
		while (j < col)
		{
			if (matrix[i][j].type == '1')
			{
				if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->border,
						(matrix[i][j].col * data->px),
						(matrix[i][j].row * data->px));
				else
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->obs,
						(matrix[i][j].col * data->px),
						(matrix[i][j].row * data->px));
			}
			j++;
		}
	}
}

void	replace_player_img(t_board **matrix, int row, int col, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < row)
	{
		j = 0;
		while (j < col)
		{
			if (matrix[i][j].type == 'N' || matrix[i][j].type == 'S'
				|| matrix[i][j].type == 'E' || matrix[i][j].type == 'W')
				draw_player(data);
			j++;
		}
	}
}

void	draw_player(t_data *data)
{
	int	i;
	int j;
//un cuadradito de 5x5 pix
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			mlx_pixel_put(data->mlx, data->mlx_win,
				data->player->x_position + i, data->player->y_position + j,
				0x000000);
			j++;
		}
		i++;
	}
	draw_view_point(data);
}

void	draw_floor2d(t_data	*data)
{
	int	i;
	int j;
//un cuadradito de 5x5 pix del color de fondo
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, data->player->x_position + i,
				data->player->y_position + j, 0xC3C3C3);
			j++;
		}
		i++;
	}
}

void draw_view_point(t_data *data)
{
	mlx_pixel_put(data->mlx, data->mlx_win, (int)(data->player->x_position + (cos(data->player->direction * M_PI / 180) * 30)),
			(int)(data->player->y_position - (sin(data->player->direction * M_PI / 180) * 30)), 0x00FF00);
}