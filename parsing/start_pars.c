/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:22:09 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 17:23:32 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*set_path(char **str)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", str[i], 5) != 0)
		i++;
	return (str[i] + 5);
}

void	help_size(int *i, char *line)
{
	while (line[*i] == ' ')
		*i += 1;
	if (line[*i] == '\0')
		return ;
}

int	help_simple(int *i, char *line)
{
	*i += 1;
	while (line[*i] && line[*i] != '\'')
		*i += 1;
	return (0);
}

int	help_double(int *i, char *line)
{
	*i += 1;
	while (line[*i] && line[*i] != '\"')
		*i += 1;
	return (0);
}

int	size_cmd_tab(char *line)
{
	t_cmdtab	d;

	d.i = 0;
	d.vu = 0;
	d.size = 1;
	while (line[d.i])
	{
		if (line[d.i] == ' ')
		{
			help_size(&d.i, line);
			if (line[d.i] == '\0' && d.vu)
				return (d.size);
		}
		if (line[d.i] == '\0')
			return (0);
		if (line[d.i] == '\'')
			help_simple(&d.i, line);
		if (line[d.i] == '\"')
			help_double(&d.i, line);
		if (line[d.i] == '|')
			d.size++;
		if (line[d.i])
		{
			d.i++;
			d.vu++;
		}
	}
	return (d.size);
}
