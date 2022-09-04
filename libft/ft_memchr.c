/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:57:01 by avaures           #+#    #+#             */
/*   Updated: 2021/12/03 21:58:36 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int car, size_t size)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	c;

	c = (unsigned char)car;
	str = (unsigned char *)s;
	i = 0;
	while (i < size)
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
