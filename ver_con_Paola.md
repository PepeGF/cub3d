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

## player_functions.c
	Ojo al tocar este archivo, hay cosas que son solo para que funcione
	pero también las hay importantes aunque no lo parezcan

## cub3d.h
typedef struct s_player
{
	double	x;				//posicion cuadricula
	double	y;
	int		x_fut;			//futura posición x en cuadrícula previa a comprobar colisiones
	int		y_fut;
	int		direction;		//angulo sexagesimal 0 = este, positivo antihorario (anguloRotacion)
	double	dir_rad;		//está bien
	int		x_position;		//posicion pixeles
	int		y_position;
	int		x_fut_pos;	//futura posicion x en pixeles previa a comprobar colisiones
	int		y_fut_pos;
	int		move_on;		//0 = parado, 1 = adelante, -1 = atrás
	int		turn_on;		//-1 = giro Izq, 1 = giro Dcha
	int		sideway_on;		//0 = parad0, -1 = derecha, 1 = izquierda
	int		move_speed;		// velocidad desplazamiento en pixeles ¿3?
	int		turn_speed;		// velocidad rotacion. 3 * PI/180 ¿3? grados pasados a radianes
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

}	t_player;


