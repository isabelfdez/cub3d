/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:52:38 by isfernan          #+#    #+#             */
/*   Updated: 2019/11/29 19:52:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	i2;
	char			*str;
	char			*s2;

	i = 0;
	i2 = 0;
	if (!s || !f)
		return (NULL);
	s2 = (char *)s;
	i = ft_strlen(s) + 1;
	if (!(str = malloc(sizeof(char) * i)))
		return (NULL);
	while (i2 < i - 1 && s2[i2])
	{
		str[i2] = (*f)(i2, s2[i2]);
		i2++;
	}
	str[i2] = 0;
	return (str);
}
