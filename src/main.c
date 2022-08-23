/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:23:07 by josgarci          #+#    #+#             */
/*   Updated: 2022/08/23 17:11:50 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_variables(t_list **list)
{
	t_list	*aux;

	aux = *list;
	while (*list)
	{
		aux = (*list)->next;
		if ((*list)->content != NULL)
			free((*list)->content);
		free(*list);
		*list = aux;
	}
}

void	free_if_error(int fd, t_list **aux)
{
	free_variables(aux);
	close(fd);
	exit (0);
}

void	check_file(char *file)
{
	int	i;

	i = ft_strlen(file) - 1;
	if (file[i] != 'b' || file[i - 1] != 'u'
		|| file[i - 2] != 'c' || file[i - 3] != '.')
	{
		printf("Error\nIncorrect file extension\n");
		exit (0);
	}
}

t_list	*ft_read_map(char *file, int cont[2])
{
	int		fd;
	char	*line;
	int		len;
	t_list	*aux;

	check_file(file);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (line == 0)
		exit(0);
	cont[1] = ft_strlen(line) - 1;
	aux = 0;
	while (line)
	{
		len = ft_strlen(line) - 1;
		if (cont[1] != len)
			free_if_error(fd, &aux);
		ft_lstadd_back(&aux, ft_lstnew(line));
		line = get_next_line(fd);
		cont[0]++;
	}
	close(fd);
	return (aux);
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_list	*list;
	int		cont[2];//solo para pruebas iniciales

	list = 0;
	list = ft_read_map(argv[1], cont);
	
	printf("Paola guapa!\n");
	return 0;
}
