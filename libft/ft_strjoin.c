/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:32:41 by isfernan          #+#    #+#             */
/*   Updated: 2019/12/06 21:23:33 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cat(char const *s1, char const *s2, char *s3)
{
	int		c[3];

	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	while (s1[c[0]])
	{
		s3[c[2]] = s1[c[0]];
		c[2]++;
		c[0]++;
	}
	while (s2[c[1]])
	{
		s3[c[2]] = s2[c[1]];
		c[2]++;
		c[1]++;
	}
	s3[c[2]] = 0;
	return (s3);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		c1;
	int		c2;

	c1 = 0;
	c2 = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[c1])
		c1++;
	while (s2[c2])
		c2++;
	if (!(s3 = malloc(sizeof(char) * (c1 + c2 + 1))))
		return (0);
	s3 = ft_cat(s1, s2, s3);
	return (s3);
}
