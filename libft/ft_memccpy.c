/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:41 by isfernan          #+#    #+#             */
/*   Updated: 2019/11/28 14:50:05 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	c1;
	unsigned char	*dst2;
	unsigned char	*src2;
	size_t			i;

	c1 = c;
	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	i = 0;
	while (i < n && src2[i] != c1)
	{
		dst2[i] = src2[i];
		i++;
	}
	if (src2[i] == c1)
	{
		dst2[i] = c1;
		return ((void *)(dst2 + i + 1));
	}
	return (NULL);
}
