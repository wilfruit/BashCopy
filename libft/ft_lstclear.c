/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:32:34 by avaures           #+#    #+#             */
/*   Updated: 2021/12/03 21:49:01 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*before;

	temp = *lst;
	while (temp != NULL)
	{
		before = temp->next;
		ft_lstdelone(temp, del);
		temp = before;
	}
	*lst = NULL;
	return ;
}
