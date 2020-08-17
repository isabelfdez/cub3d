#include <mlx.h>

int     main(void)
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *relative_path = "./textures/bluestone.xpm";
    int     img_width;
    int     img_height;

    img_width = 300;
    img_height = 300;
    mlx = mlx_init();
    win = mlx_new_window(mlx, 300, 450, "texture");
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
}