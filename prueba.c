/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:54:57 by isfernan          #+#    #+#             */
/*   Updated: 2020/07/21 18:26:26 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <math.h>
#include <stdio.h>

// Esto imprime la imagen del ágila

int     main(void)
{
    void    *mlx;
	void	*win;
    void    *img;
    char    *relative_path = "./textures/eagle.xpm";
    int     img_width;
    int     img_height;

	img_width = 700;
	img_height = 700;
    mlx = mlx_init();
	win = mlx_new_window(mlx, 700, 700, "prueba");
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	printf("%s", img);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
}
