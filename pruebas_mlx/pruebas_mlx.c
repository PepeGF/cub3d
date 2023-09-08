# include <stdio.h>
# include <mlx.h>
#include <math.h>
#include "../libft/libft.h"
// # define width 640
// # define heigth 360

/* int *ft_get_color_from_strings(char *array[2][3])
{
	int *colors;
	int	i;
	int	j;
	int	aux[2][3];

	colors = malloc(sizeof(int) * 2);
	i = 0;
	while(i < 2)
	{
		j = 0;
		while (j < 3)
		{
			aux[i][j] = ft_atoi(array[i][j]);
			j++;	
		}
		i++;
	}
	colors[0] = (aux[0][0] << 24) + (aux[0][1] << 16) + (aux[0][2] << 8);
	colors[1] = (aux[1][0] << 24) + (aux[1][1] << 16) + (aux[1][2] << 4);
	return colors;
}

void	leaks()
{
	system("leaks wololo");
}

int main()
{
	atexit(leaks);
	char *array[2][3] = {
		{"100", "0", "200"},
		{"10", "250", "30"}
	};
	int *colors;

	colors = ft_get_color_from_strings(array);
	printf("floor: %d\nsky: %d\n", colors[0], colors[1]);
	free (colors);

	
	return 0;
}
*/



# define width 640
# define heigth 360
int main()
{
	printf("%f\n", (double)1 / (double)0);
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, width, heigth, "Tutorial Window - Create Image");

	void *image = mlx_new_image(mlx, width, heigth);
	
	int pixel_bits;
	int line_bytes;
	int endian;
	int *buffer = (int *)mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	line_bytes /= 4;
	int color = 0xABCDEF;
	for(int y = 0; y < heigth/2; ++y)
	for(int x = 0; x < 640; ++x)
	{
		buffer[(y * line_bytes) + x] = color;
	}
	color = 0x123456;
	for (int y = heigth/2; y < heigth; ++y)
	for(int x = 0; x < 640; ++x)
	{
		buffer[(y * line_bytes) + x] = color;
	}
	//aquí una columna de pixeles negros en x = witdh * 0.66
	for (int y = 40; y < heigth - 40; ++y)
    {
        buffer[(y * line_bytes) + 300] = 0xFF0000;
    }
	printf("pixel_bits: %d\nline_bytes: %d\nendia: %d\n", pixel_bits, line_bytes, endian);

	mlx_put_image_to_window(mlx, win, image, 0, 0);
	

	mlx_loop(mlx);
	return 0;
}


/* int main()
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, width, heigth, "Tutorial Window - Create Image");

	void *image = mlx_new_image(mlx, width, heigth);
	
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);

	printf("pixel_bits: %d\nline_bytes: %d\nendia: %d\n", pixel_bits, line_bytes, endian);
	int color = 0xABCDEF;

printf("color antes: %d\n", color);
    color = mlx_get_color_value(mlx, color);
printf("color después: %d\n", color);

for(int y = 0; y < heigth/2; ++y)
for(int x = 0; x < 640; ++x)
{
    int pixel = (y * line_bytes) + (x * 4);
    //else if (endian == 0)   // Least significant (Blue) byte first
    
	buffer[pixel + 0] = (color) & 0xFF;
	buffer[pixel + 1] = (color >> 8) & 0xFF;
	buffer[pixel + 2] = (color >> 16) & 0xFF;
	buffer[pixel + 3] = (color >> 24);
    
}
color = 0x123456;
if (pixel_bits != 32)
    color = mlx_get_color_value(mlx, color);

for (int y = heigth/2; y < heigth; ++y)
for(int x = 0; x < 640; ++x)
{
	int pixel = (y * line_bytes) + (x * 4);
    //else if (endian == 0)   // Least significant (Blue) byte first
    
	buffer[pixel + 0] = (color) & 0xFF;
	buffer[pixel + 1] = (color >> 8) & 0xFF;
	buffer[pixel + 2] = (color >> 16) & 0xFF;
	buffer[pixel + 3] = (color >> 24);
}

	mlx_put_image_to_window(mlx, win, image, 0, 0);
	// The following code goes here.

	mlx_loop(mlx);
}
 */