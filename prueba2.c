/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:55:35 by isfernan          #+#    #+#             */
/*   Updated: 2020/07/02 17:42:42 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef	struct	s_prueba2
{
	void    *mlx_ptr;
    void    *win_ptr;
}				t_prueba2;


void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	long int		i;
	unsigned int	n2;

	i = 1;
	if (n == 0)
		write(fd, "0", 1);
	else
	{
		if (n < 0)
		{
			n2 = n * (-1);
			write(fd, "-", 1);
		}
		else
			n2 = n;
		while (n2 / i != 0)
			i = i * 10;
		while (i >= 10)
		{
			c = (n2 % i) / (i / 10) + '0';
			write(fd, &c, 1);
			i = i / 10;
		}
	}
}

int key_pressed(int key, void *param)
{
	int	i;
	t_prueba2 *p2;

	p2 = (t_prueba2 *)param;
	i = -1;
    ft_putnbr_fd(key, 1);
	while (++i < 500)
		mlx_pixel_put(p2->mlx_ptr, p2->win_ptr, 50, i, 0xFFEA03);
    return (0);
}

int main()
{
	t_prueba2 *p2;

	p2 = malloc(sizeof(t_prueba2));

    p2->mlx_ptr = mlx_init();
    p2->win_ptr = mlx_new_window(p2->mlx_ptr, 500, 500, "42");
    mlx_key_hook(p2->win_ptr, key_pressed, p2);
    mlx_loop(p2->mlx_ptr);
    return (0);
}