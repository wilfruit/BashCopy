/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:27:21 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 17:03:16 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_init_cmdtab(t_cmdtab *data)
{
	data->i = 0;
	data->vu = 0;
	data->size = 1;
}

void	add_node_to_env(t_envi *list, char *str)
{
	t_envi	*temp;
	t_envi	*cursor;

	cursor = list;
	temp = ft_calloc(sizeof(t_envi), 1);
	temp->str = ft_strdup(str);
	temp->next = NULL;
	while (cursor && cursor->next)
		cursor = cursor->next;
	cursor->next = temp;
	return ;
}

void	add_node_to_exp(t_envi *list, char *str)
{
	t_envi	*temp;
	t_envi	*cursor;
	char	**av;
	char	*equalblank;

	cursor = list;
	av = ft_split(str, '=');
	temp = ft_calloc(sizeof(t_envi), 1);
	if ((av && av[0] && av[1]) || !ft_strchr(str, '='))
		temp->str = ft_strdup(str);
	else
	{
		equalblank = ft_strjoin(str, "''");
		temp->str = ft_strdup(equalblank);
		free (equalblank);
	}
	temp->next = NULL;
	while (cursor && cursor->next)
		cursor = cursor->next;
	cursor->next = temp;
	ft_free_chr(av);
	return ;
}

char	**no_assign_export(char *str)
{
	char	**av;

	av = (char **)malloc(sizeof(char *) * 2);
	if (!av)
		perror("Malloc : ");
	av[0] = ft_strdup(str);
	av[1] = NULL;
	return (av);
}

int	ft_nt_att(t_envi *env, char *av)
{
	t_envi	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, av, ft_strlen(av)) == 0)
		{
			if (ft_strchr(tmp->str, '='))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
