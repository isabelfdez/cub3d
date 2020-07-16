/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:57:51 by isfernan          #+#    #+#             */
/*   Updated: 2020/07/16 18:44:55 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>

typedef struct  s_data 
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef	struct	s_window
{
	void	*ptr;
	void	*win;
	t_data	image;
}				t_window;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	other_function(t_window *test)
{
	t_data  	img;
	int			x;
	int			start;
	int			end;
	int			i;


	start = 0;
	end = 1080;
	x = 0;
    img.img = mlx_new_image(test->ptr, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	while (x < 1080)
	{
		i = 0;
		while (i < start)
		{
			my_mlx_pixel_put(&img, x, i, 0x00000000);
			i++;
		}
		while (i < end)
		{
			my_mlx_pixel_put(&img, x, i, 0x00FF0000);
			i++;
		}
		while (i < 300)
		{
			my_mlx_pixel_put(&img, x, i, 0x00000000);
			i++;	
		}
		start++;
		end--;
		x++;
	}
	test->image = img;
}

int             main(void)
{
    t_window	*test;

	test = malloc(sizeof(t_window));
	test->ptr = mlx_init();
	test->win = mlx_new_window(test->ptr, 1920, 1080, "Hello world!");
	other_function(test);
	mlx_put_image_to_window(test->ptr, test->win, test->image.img, 0, 0);
    mlx_loop(test->ptr);
}