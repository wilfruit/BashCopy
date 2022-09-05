/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nested_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:14:53 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/05 17:35:45 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**build_nested_command(t_shell *data, int cell_nb, char **args)
{
	t_nested	nest;

	nest.j = 0;
	nest.i = 0;
	nest.k = 0;
	nest.exp = (char **)malloc(sizeof(char *) * (count_args(data, cell_nb) + search_in_charray(args, 34) + 1));
	if (!nest.exp)
		return (NULL);
	while (args[nest.i])
	{
		if (ft_strchr(args[nest.i], ' ') && !ft_strchr(args[nest.i], 34))
		{
			nest.split = ft_split(args[nest.i], ' ');
			nest.j = 0;
			while (nest.split[nest.j])
			{
				nest.exp[nest.k] = ft_strdup(nest.split[nest.j]);
				nest.k++;
				nest.j++;
			}
		}
		nest.i++;
	}
	nest.exp[nest.k] = NULL;
	ft_free_chr(nest.split);
	ft_free_chr(args);
	return (nest.exp);
}
