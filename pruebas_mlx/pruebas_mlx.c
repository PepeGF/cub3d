# include <stdio.h>
# include <mlx.h>
#include <math.h>
#include <unistd.h>
#include "../libft/libft.h"
# define width 640
# define heigth 360

typedef struct s_image
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_image;

void put_pixel_img(t_image game, int x, int y, int color)
{
	char *dst;
// printf("x: %d | y: %d\n", x, y);
	dst = game.addr + (y * game.line_length + x * (game.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int main()
{
	t_image texture;
	t_image game;
	int color;
	(void)game;
	// vamos a crear una textura a partir de un archivo xpm
	texture.mlx = mlx_init();
	texture.win = mlx_new_window(texture.mlx, width, heigth, "Tutorial Window - Create Image");
	texture.img = mlx_xpm_file_to_image(texture.mlx, "WE.XPM", &texture.line_length, &texture.bits_per_pixel);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
	printf("bits_per_pixel: %d\tline_length: %d\tendian: %d\n", texture.bits_per_pixel, texture.line_length, texture.endian);

// Fila y columna del píxel que deseas obtener
	int x = 10;
	int y = 15;

	// Calcular el índice del píxel en función de la fila y columna
	int index = (y * texture.line_length) + (x * (texture.bits_per_pixel / 8));
	printf("Index: %d\n", index);

	// Acceder a los componentes de color (RGBA) en el píxel
	unsigned char blue = texture.addr[index];
	unsigned char green = texture.addr[index + 1];
	unsigned char red = texture.addr[index + 2];

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, width, heigth, "Game");
	game.img = mlx_new_image(game.mlx, width, heigth);
	game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel, &game.line_length, &game.endian);
	
	color = (red << 16) | (green << 8) | blue;
	color = ((unsigned char)(texture.addr[index + 2]) << 16) | ((unsigned char)(texture.addr[index + 1]) << 8) | (unsigned char)(texture.addr[index]);

	x = 0;
	y = 0;
	while(y < heigth)
	{
		x = 0;
		while(x < width)
		{
			put_pixel_img(game, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	printf("Color del píxel (%d, %d): RGB(%u, %u, %u)\n", x, y, red, green, blue);
	printf("Color del píxel (%d, %d): RGB(%02X%02X%02X)\n", x, y, red, green, blue);
	printf("Color del píxel (%d, %d): RGB(%X)\n", x, y, color);

	mlx_loop(game.mlx);
	return 0;

}









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

/* int main()
{

	// crea una ventana de 640x360 y le pone la mitad superior de un color y la mitad inferior de otro
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
 */

/* int main()
{ // la mismo que el anterior pero con un código más complicado
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

