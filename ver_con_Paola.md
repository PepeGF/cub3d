## images.c:texture_malloc

Esto tiene que venir dado del parseo del archivo del mapa, ojo, reservando la memoria antes:
	data->no->path = ft_strdup("./img/NO.xpm");
	data->so->path = ft_strdup("./img/SO.xpm");
	data->ea->path = ft_strdup("./img/EA.xpm");
	data->we->path = ft_strdup("./img/WE.xpm");

## images.c:initialize_images

Esto tiene que venir dado del parseo del archivo del mapa:
	data->sky_color = 0xABCDEF;
	data->floor_color = 0x123456;

## read_file.c:all

Este archivo solo se mantiene para poder ejecutar lo demás:
	ft_read_map:15
	//esto no valdrá, el mapa no tiene xq ser rectangular
	ft_read_map:20
	/* 		if (data->map_x_tot != len)//no vale, las lineas no tienen q ser guales
			free_if_error(fd, &aux); */

## main.c
	list = ft_read_map(argv[1], data);
	Esto sobra o tiene que ser ampliamente modificado

	Quitar la funcion leaks

	Quitar variable data->debug

## matrix.c
	Creo que este archivo en general, al juntarlo todo, debería desaparecer




