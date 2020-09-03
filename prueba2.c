/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:55:35 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/03 17:13:47 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	void	*mlx;
	char	*path = "./hola.xpm";
	int		w = 64;
	int		h = 64;
	void	*img;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	printf("%s", img);
}