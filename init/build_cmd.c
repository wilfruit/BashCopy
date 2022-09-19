/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:22:47 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/09 00:55:22 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	count_args(t_shell *data, int cell_nb)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (i < data->token[cell_nb].nb_token)
	{
		if (data->token[cell_nb].scmd[i].type == TOKEN_ARG \
		&& ft_strlen(data->token[cell_nb].scmd[i].value) > 0)
			count++;
		i++;
	}
	return (count);
}

int	has_space_in(t_shell *data, int cell_nb)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (data->token[cell_nb].scmd[i].type != TOKEN_CMD)
		i++;
	while (i < data->token[cell_nb].nb_token && \
	data->token[cell_nb].scmd[i].type == TOKEN_ARG)
	{
		if (ft_strchr(data->token[cell_nb].scmd[i].value, ' '))
			n++;
		i++;
	}
	return (n);
}

int	search_in_charray(char **super, char needle)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (super[i])
	{
		j = 0;
		while (super[i][j])
		{
			if (super[i][j] == needle && !ft_strchr(super[i], 61))
				n++;
			j++;
		}
		i++;
	}
	return (n);
}

void	fill_args(t_shell *data, int cell_nb, int i, char **args)
{
	int		j;

	j = 1;
	while (i < count_args(data, cell_nb) \
	&& i < data->token[cell_nb].nb_token && \
	data->token[cell_nb].scmd[i].type == TOKEN_ARG)
	{
		if (data->token[cell_nb].scmd[i].type == TOKEN_ARG)
		{
			if (data->token[cell_nb].scmd[i].is_dollar == 0)
				args[j] = ft_strdup(data->token[cell_nb].scmd[i].value);
			else
				args[j] = dollar_swap(data, \
			ft_strdup(data->token[cell_nb].scmd[i].value));
			j++;
		}
		i++;
	}
	args[j] = NULL;
	if (args[0] == NULL && args[1] != NULL)
		args++;
}

char	**build_command(t_shell *data, int cell_nb)
{
	char	**args;
	int		i;

	i = 0;

	args = (char **)malloc(sizeof(char *) * (count_args(data, cell_nb) + 1));
	if (!args)
		return (NULL);
	while (i < data->token[cell_nb].nb_token \
	&& data->token[cell_nb].scmd[i].type != TOKEN_CMD)
		i++;
	if (ft_strlen(data->token[cell_nb].scmd[i].value) == 0)
		args[0] = ft_strdup(" ");
	else if (data->token[cell_nb].scmd[i].is_dollar == 0)
		args[0] = ft_strdup(data->token[cell_nb].scmd[i].value);
	else
		args[0] = dollar_swap(data, \
		ft_strdup(data->token[cell_nb].scmd[i].value));
	i++;
	fill_args(data, cell_nb, i, args);
	if (search_in_charray(args, ' ') && ft_is_dollar_cmd(data, cell_nb))
		return (build_nested_command(data, cell_nb, args));
	return (args);
}
