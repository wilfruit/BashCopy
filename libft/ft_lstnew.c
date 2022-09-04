/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:06:30 by avaures           #+#    #+#             */
/*   Updated: 2021/12/03 21:55:03 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*sheesh;

	sheesh = malloc(sizeof(t_list));
	if (!sheesh)
		return (NULL);
	sheesh->content = content;
	sheesh->next = NULL;
	return (sheesh);
}
