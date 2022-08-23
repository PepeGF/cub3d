/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:23:07 by josgarci          #+#    #+#             */
/*   Updated: 2022/08/23 17:03:07 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int main(int argc, char const *argv[])
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
