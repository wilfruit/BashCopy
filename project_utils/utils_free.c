/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:04:20 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 17:04:21 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_init_cmdpipe(t_manage_pipe *mpipe)
{
	mpipe->i = 0;
	mpipe->j = 0;
	mpipe->size = 0;
}

void	free_exec_pack(t_exec_single *pack)
{
	ft_free_chr(pack->allpaths);
	ft_free_chr(pack->cmdargs);
	if (pack->cmdstat)
		free(pack->cmdstat);
}

void	ft_free_chr(char **super)
{
	int	i;

	i = 0;
	while (super[i])
	{
		free(super[i]);
		i++;
	}
	free(super);
	super = NULL;
}

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	ft_free_env(t_envi *head)
{
	t_envi	*current;
	t_envi	*next;

	current = head;
	next = NULL;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}
