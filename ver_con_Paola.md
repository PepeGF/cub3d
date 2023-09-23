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

