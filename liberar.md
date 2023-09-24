images.c:texture_malloc

data->no = (t_img *)malloc(sizeof(t_img));
data->so = (t_img *)malloc(sizeof(t_img));
data->ea = (t_img *)malloc(sizeof(t_img));
data->we = (t_img *)malloc(sizeof(t_img));

data->no->path = ft_strdup("./img/NO.xpm");
data->so->path = ft_strdup("./img/SO.xpm");
data->ea->path = ft_strdup("./img/EA.xpm");
data->we->path = ft_strdup("./img/WE.xpm");

images.c:initialize_images
data->cub3d_image = malloc(sizeof(t_img));

main.c:main
data = (t_data *)malloc(sizeof(t_data));

player_functions.c:where_is_the_player
player = malloc(sizeof(t_player));

matrix.c:ft_final_matrix
board = malloc(sizeof(t_board *) * (data->map_y_tot));
board[i] = malloc(sizeof(t_board) *(data->map_x_tot));

raycast_aux.c:initialize_ray
ray = malloc(sizeof(t_ray) * WIN_WIDTH);
ray[i] = malloc(sizeof(t_ray));
