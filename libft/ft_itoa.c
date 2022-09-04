/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:11:36 by avaures           #+#    #+#             */
/*   Updated: 2021/12/04 11:47:07 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	count_itoa(int n)
{
	unsigned int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_build_itoa(char *res, unsigned int len, int n)
{
	unsigned int	i;
	int				negativ;

	negativ = 0;
	if (n < 0)
		negativ = 1;
	if (n == 0)
		res[0] = '0';
	i = 0;
	while (n != 0)
	{
		if (negativ)
			res[len - i - 1] = '0' - (n % 10);
		else
			res[len - i - 1] = '0' + (n % 10);
		n = n / 10;
		i++;
	}
	if (negativ)
		res[0] = '-';
	res[len] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;

	len = count_itoa(n);
	if (n < 0)
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	return (ft_build_itoa(res, len, n));
}
