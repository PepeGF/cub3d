images.c:texture_malloc

data->no = (t_img *)malloc(sizeof(t_img));
data->so = (t_img *)malloc(sizeof(t_img));
data->ea = (t_img *)malloc(sizeof(t_img));
data->we = (t_img *)malloc(sizeof(t_img));

data->no->path = ft_strdup("./img/NO.xpm");
data->so->path = ft_strdup("./img/SO.xpm");
data->ea->path = ft_strdup("./img/EA.xpm");
data->we->path = ft_strdup("./img/WE.xpm");
