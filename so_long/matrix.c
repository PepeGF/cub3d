/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:51:28 by pmoreno-          #+#    #+#             */
/*   Updated: 2023/08/23 20:33:01 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_initialize_pos(t_board *elem)
{
	elem->col = -1;
	elem->row = -1;
	elem->is_border = 0;
	elem->type = 'N';//esto no se puede hacer aquí, se puede, pero no sirve de nada
	elem->coll = 0;
//	elem->end = 0;
	elem->jug = 0;
}

t_board	ft_add_element_to_list(char c, int row, int col)
{
	t_board	elem;

	ft_initialize_pos(&elem);
	elem.col = col;
	elem.row = row;
	elem.type = c;
	if (c == '1')
		elem.is_border = 1;
	// else if (c == 'C')
		elem.coll = 1;
	/* else if (c == 'E')
		elem.end = 1; */
	//else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	//	elem.jug = 1;
	//elem.end = 1;//para que el checker no llore aunque sea mentira
	return (elem);
}


int ft_strlen_list(t_list *aux)
{
	int j;

	j = 0;
	while (aux->content[j])
		j++;
	return j;
}


void print_new_matrix(t_board **matrix, int rows, int len)
{
	int r;
	int col;

	r = 0;

	//printf("%c", matrix[0][0].type);
	while (r < rows && matrix[r])
	{
		//printf("HOLA");
		col = 0;
		while (col < len && matrix[r][col].type)
		{
			//printf("HOLA");
			printf("%c", matrix[r][col].type);
			col++;
		}
		printf("\n");
		r++;
	}
}


void	initialize_bg(t_background *bg)
{
	bg->rgb_color = 0;
	bg->ncolor = 0;
}


int is_rgb_color(t_list *aux, char type, int pos)
{
	t_background bg;
	int 	i;
	char	*color;
	char	*aux2;
	int		num;
	char	a;

	i = pos;
	num = 0;
	printf("Aqui llega\n");
	initialize_bg(&bg);
	bg.rgb_color = ft_calloc(sizeof(char *), 4);
	while (aux->content[i] == ' ' || aux->content[i] == '\t' || aux->content[i] == type)
		i++;
	printf("Quitando espacios del principio\n");
	if (aux->content[i] == '\n' || ft_isdigit(aux->content[i]) == 0)
	{
		printf("Error. NO HAY COLOR\n");
		return -6;
	}
	else
	{
		//no usar split
		color = ft_calloc(sizeof(char), 1);
		while (aux->content[i])
		{
			if (ft_isdigit(aux->content[i]) == 1 || (aux->content[i] == ' ' || (aux->content[i] == '\t')))
			{
				//printf("Añadiendo numero %c a color\n", aux->content[i]);
				a = aux->content[i];
				aux2 = ft_strlcat_gnl(color, &a);
				if (color)
					free(color);
				color = aux2;
				//printf("%s\n", color);
			}
			else
			{

				if (aux->content[i] == ',' || aux->content[i] == '\n' )
				{
					//printf("Llegamos a la coma con el numero %s\n", color);
					num = ft_atoi(color);

					if (num >= 0 && num <= 255)
					{
						printf("El número %d si que vale para el color final. Pasar a variable\n\n", num);
						if (aux2)
							free(aux2);
						bg.rgb_color[bg.ncolor] = ft_itoa(num);
						bg.ncolor++;
						color = ft_calloc(sizeof(char) , 1);
						num = 0;
					}
					else
					{
						if (aux2)
							free(aux2);
						free(color);
						printf("Error. RGB NO VÁLIDO\n");
						return -7;
					}
					
				}
				else
				{
					printf("Error. CARACTER NO VÁLIDO\n");
					return -8;
				}
			}
			i++;
		}
		if (color)
			free(color);
	}
	i = 0;
	printf("El color final es: ");
	while (i < bg.ncolor){
		if (i != 2)
			printf("%s, ", bg.rgb_color[i]);
		if (i == 2)
			printf("%s\n", bg.rgb_color[i]);
		i++;
	}
	//return bg;
	return 0;
}

/*
char *is_rgb_color3(t_list *aux, char type)
{
	int 	i;
	char	*linea;
	char	*color;
	char	*aux2;
	int		num;
	char	a;
	int		j;

	i = 0;
	num = 0;
	j = 0;
	printf("Aqui llega\n");
	linea = calloc(sizeof(char), 1);
	while (aux->content[i])
	{
		a = aux->content[i];
		aux2 = ft_strlcat_gnl(linea, &a);
		if (linea)
			free(linea);
		linea = aux2;
		i++;
	}
	i = 0;
	aux = 0;
	printf("Linea: %s", linea);
	while (linea[i] == ' ' || linea[i] == '\t' || linea[i] == type)
		i++;
	j = i;
	printf("Quitando espacios del principio\n");
	if (linea[i] == '\n' || ft_isdigit(linea[i]) == 0)
	{
		printf("Error. NO HAY COLOR\n");
		return NULL;
	}
	else
	{
		printf("Parece que llega a un número\n");
		//no usar split
		color = calloc(sizeof(char), 1);
		while (linea[i])
		{
			a = linea[i];
			if (ft_isdigit(a) == 1 || (a == ' ' || (a == '\t')))
			{
				printf("Añadiendo numero %c a color\n", a);
				aux2 = ft_strlcat_gnl(color, &a);
				if (color)
					free(color);
				color = aux2;
				printf("Color: %s\n", color);
			}
			else
			{
				if (a == ',' || a == '\n' )
				{
					printf("Llegamos a la coma con el numero %s\n", color);
					num = ft_atoi(color);
					if (num >= 0 && num <= 255)
					{
						printf("El número %d si que vale para el color final. Pasar a variable\n\n", ft_atoi(color));
						if (aux2)
							free(aux2);
						color = calloc(sizeof(char) , 1);
						num = 0;
					}
					else
					{
						if (aux2)
							free(aux2);
						free(color);
						printf("Error. RGB NO VÁLIDO\n");
						return NULL;
					}
					
				}
				else
				{
					printf("Error. CARACTER NO VÁLIDO\n");
					return NULL;
				}
			}
			i++;
		}
	}
	return &linea[j];
}


char	**is_rgb_color_var(t_list *aux, char type)
{
	int 	i;
	int		j;
	char	*color;
	char	*aux2;
	char	**rgb;
	char	**aux3;
	int		num;
	char	a;

	i = 0;
	j = 0;
	num = 0;
	printf("Aqui llega\n");
	while (aux->content[i] == ' ' || aux->content[i] == '\t' || aux->content[i] == type)
		i++;
	printf("Quitando espacios del principio\n");
	if (aux->content[i] == '\n' || ft_isdigit(aux->content[i]) == 0)
	{
		printf("Error. NO HAY COLOR\n");
		return NULL;
	}
	else
	{
		
		printf("Parece que llega a un número\n");
		color = calloc(sizeof(char), 1);
		while (aux->content[i] != '\n')
		{
			if (ft_isdigit(aux->content[i]) == 1 || (aux->content[i] == ' ' || (aux->content[i] > 8 && aux->content[i] < 14)))
			{
				printf("Añadiendo numero %c a color\n", aux->content[i]);
				a = aux->content[i];
				aux2 = ft_strlcat_gnl(color, &a);
				if (color)
					free(color);
				color = aux2;
				aux2 = 0;
				printf("%s\n", color);
			}
			else
			{
				free(color);
				printf("Error. CARACTER INVÁLIDO\n");
				return NULL;
			}
			i++;
		}
		aux3 = ft_split(color, ',');
		i = 0;
		rgb = calloc(sizeof(char *), 4);
		while (aux3[i])
		{
			num = ft_atoi(aux3[i]);
			if (num >= 0 && num <= 255)
			{
				rgb[j] = ft_itoa(num);
				j++;
				printf("El número %d si que vale para el color final. Pasar a variable\n\n", num);
			}
			else
			{
				//if (aux2)
				free(aux2);
				free(color);
				//if (*rgb)
				//	free(*rgb);
				free(rgb);
				//free(aux3);
				printf("Error. RGB NO VÁLIDO\n");
				return NULL;
			}
			i++;
		}
			
	}
	//rgb = ft_split(color, ',');
	return rgb;
}
*/

//char **get_file_texture(t_list *aux, int j)
int	get_file_texture(t_list *aux, int j)
{
	while (aux->content[j] == ' ' || aux->content[j] == '\t')
		j++;
	if ((aux->content[j] == '.' && aux->content[j + 1] != '/') || (aux->content[j] != '.'))
	{
		printf(" ---> FALLO\n");
		return -1;
	}
	else
	{
		printf(" ---> TA BIEN\n");
		return 1;
	}
}


int	check_end_matrix(int rows, int matrix)
{
	if (rows < 2 && matrix == 1)
		return -3;
	if (matrix == 1)
		return 1;
	return 0;
}


int	check_direction(char a, char b)
{
	printf("\n");
	if (a == 'N' && b == 'O')
	{
		printf("ES %c%c", a, b);
		return 1;
	}
	if (a == 'S' && b == 'O')
	{
		printf("ES %c%c", a, b);
		return 2;
	}
	if (a == 'E' && b == 'A')
	{
		printf("ES %c%c", a, b);
		return 3;
	}
	if (a == 'W' && b == 'E')
	{
		printf("ES %c%c", a, b);
		return 4;
	}
	return 0;
}


void	check_final_matrix(t_board **matrix)//, int cont[2])
{
	int r;
	int col;
	int r2;
	//int col2;

	r = 0;
	while (matrix[r])
	{
		col = 0;
		while (matrix[r][col].type)
		{
			if (matrix[r][col].type == 'P')
				break;
			col++;
		}
		printf("\n");
		r++;
	}
	r2 = 0;

	while (matrix[r2][col].type != '1')
		r2++;

	//col2 = col;
/*	while ((r2 >= 0 && r2 <= cont[1]) && (col2 >= 0 && col2 <= cont[0]))
	{
		
	}
*/
	
}



int ft_final_matrix(t_list **list, int cont[2])
{
	t_board	**board;
	t_list	*aux;
	int		max;
	int		j;
	int		pos_r;
	int 	pos_c;
	int		is_matrix;
	int		end;

	aux = *list;
	pos_r = 0;
	max = 0;
	is_matrix = 0;
	end = 0;
	board = malloc(sizeof(t_board *) * (cont[1])); //bien
	while (aux)
	{
		j = 0;
		
		while (aux->content[j])
		{
			//printf("%c", aux->content[j]);
			while (aux->content[j] == ' ' || aux->content[j] == '\t')
				j++;
			if (check_direction(aux->content[j], aux->content[j + 1]))
			{
				end = check_end_matrix(pos_r, is_matrix);
				if (end == -3)
					return -3;
				j = j + 2;
				if(get_file_texture(aux, j) == 1)
					break;
				else
					return -1;
				
			}
			else 
			{
				if (aux->content[j] == 'F' || aux->content[j] == 'C')
				{
					if (pos_r < 2 && is_matrix == 1)
						return -3;
					if (is_matrix == 1)
						end = 1;
					j++;
					if (is_rgb_color(aux, aux->content[j], j + 1) == 0)
					//if (is_rgb_color_var(aux, 'F') == NULL)	
					{
						printf("COLOR VÁLIDO\n");
						//guardar los numeros
						//pensar si dar error o si poner uno por defecto
						break ;
					}
					else
						return -9;
				}
				else
				{
					if (aux->content[j] == '1')
					{
						if (end == 1)
							return -4;
						is_matrix = 1;
						pos_c = 0;
						if ((ft_strlen_list(aux) - 1) > max)
							max = (ft_strlen_list(aux) - 1);
						board[pos_r] = malloc(sizeof(t_board) * (cont[0])); //bien
						while (aux->content[pos_c] != '\0' && aux->content[pos_c] != '\n')
						{
							/*
							printf("Longitud de la lista %d - ",ft_strlen_list(aux));
							printf("Fila %d - ", pos_r);
							printf("Columna %d - ", pos_c);
							printf("Contenido %c\n", aux->content[pos_c]);
							*/
							//error si la letra es distinta de N, S, E, W, 1 o 0 pensar si hacerlo despues de tener la matriz o ahora (mejor ahora)
							//falta pasar la linea mas larga para rellenar. hacer un join con espacios? se podria hacer aqui
							//board[pos_r][pos_c] = ft_add_element_to_list(aux->content[pos_c], pos_r, pos_c);
							board[pos_r][pos_c].row = pos_r;
							board[pos_r][pos_c].col = pos_c;
							if (aux->content[pos_c] == ' ' || aux->content[pos_c] == '\t')
								board[pos_r][pos_c].type = '-';
							else
								board[pos_r][pos_c].type = aux->content[pos_c];
							if (aux->content[pos_c] == '1')
								board[pos_r][pos_c].is_border = 1;
							else
								board[pos_r][pos_c].is_border = 0;
							if (aux->content[pos_c] == 'N' || aux->content[pos_c] == 'S' || aux->content[pos_c] == 'E' || aux->content[pos_c] == 'W')
								board[pos_r][pos_c].jug = 1;
							else
								board[pos_r][pos_c].jug = 0;
							board[pos_r][pos_c].checked = 0;
								// hacer otra funcion que mire si hay un jugador o libere
							//printf("%c", board[pos_r][pos_c].type);
							//despues de la matriz entera en el check mirar si no hay jugador
							pos_c++;
						}
						while(pos_c < cont[0])
						{
							board[pos_r][pos_c].row = pos_r;
							board[pos_r][pos_c].col = pos_c;
							board[pos_r][pos_c].type = '-';
							board[pos_r][pos_c].is_border = 0;
							board[pos_r][pos_c].jug = 0;
							pos_c++;
						}
						board[pos_r][pos_c].type = '\0';
						pos_r++;
						break;
					}
					else
					{
						if (aux->content[j] == '\n' || aux->content[j] == '\0')
							break ;
						else{
							printf("Error. BAD CHARACTER\n");
							return -5;
						}
					}
				}
			}
			j++;
		}
		aux = aux->next;
	}
	print_new_matrix(board, cont[1], cont[0]);
	system("leaks so_long");
	//return (board);
	return 0;
}


