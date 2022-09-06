/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nested_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:14:53 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 15:14:20 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int		count_built_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_is_dollar_cmd(t_shell *data, int cell_nb)
{
	int	i;

	i = 0;
	while (data->token[cell_nb].scmd[i].type != TOKEN_CMD)
		i++;
	if (data->token[cell_nb].scmd[i].type == TOKEN_CMD \
	&& data->token[cell_nb].scmd[i].is_dollar == 1)
		return (1);
	return (0);
}

int	count_worder(char *str)
{
	int	i;
	int	count;

	count = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] && (str[i] > 33 && str[i] < 127))
		{
			count++;
			while (str[i] && (str[i] > 33 && str[i] < 127))
				i++;
		}
		while (str[i] && !(str[i] > 33 && str[i] < 127))
			i++;
	}
	return (count);
}

char	**build_nested_command(t_shell *data, int cell_nb, char **args)
{
	t_nested	nest;

	nest.j = 0;
	nest.i = 0;
	nest.k = 0;
	nest.exp = (char **)malloc(sizeof(char *) * (count_built_args(args) + count_worder(args[0]) + 1));
	if (!nest.exp)
		return (NULL);
  	while (nest.i < (count_built_args(args) + count_worder(args[0]) && args[nest.i]))
	{
		if (nest.i == 0 && ft_strchr(args[nest.i], ' ') && !ft_strchr(args[nest.i], 34))
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
		else
		{
			nest.exp[nest.k] = ft_strdup(args[nest.i]);
			nest.k++;
		}
		nest.i++;
  	}
	nest.exp[nest.k] = NULL;
	//ft_free_chr(nest.split);
	ft_free_chr(args);
	return (nest.exp);
}
