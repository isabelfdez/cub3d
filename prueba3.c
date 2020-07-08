/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:57:51 by isfernan          #+#    #+#             */
/*   Updated: 2020/07/08 19:09:39 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int main()
{
	void    *mlx_ptr;
	void    *win;
	void    *img;
	char    *path = "./mario.png";
	//int     h = 50;
	//int		w = 50;

	mlx_ptr = mlx_init();
	
	win = mlx_new_window(mlx_ptr, 400, 300, "test");
	img = mlx_new_image(mlx_ptr, 400, 300);
	mlx_put_image_to_window(mlx_ptr, win, path, 0, 0);
	mlx_loop(mlx_ptr);
	//mlx_put_image_to_window(mlx_ptr, win, img, 70, 70);

}