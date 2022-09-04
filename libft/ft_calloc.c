/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:15:13 by avaures           #+#    #+#             */
/*   Updated: 2021/12/03 21:16:38 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t n_elem, size_t elem_size)
{
	void	*res;	

	res = malloc(n_elem * elem_size);
	if (!res)
		return (NULL);
	ft_bzero(res, n_elem * elem_size);
	return (res);
}
