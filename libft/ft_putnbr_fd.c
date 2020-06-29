/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:16:45 by isfernan          #+#    #+#             */
/*   Updated: 2019/11/16 18:54:06 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
