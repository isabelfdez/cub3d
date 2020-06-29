/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 21:08:25 by isfernan          #+#    #+#             */
/*   Updated: 2019/11/28 14:51:23 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_cast;
	unsigned char	c2;
	size_t			i;

	s_cast = (unsigned char *)s;
	i = 0;
	c2 = c;
	while (i < n)
	{
		if (s_cast[i] == c2)
			return ((void *)s_cast + i);
		i++;
	}
	return (NULL);
}
