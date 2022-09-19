/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_stuct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:45:53 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 14:45:55 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	set_struct(char **line, t_manage_pipe utils, t_pipe **prompt)
{
	int	i;
	int	j;

	i = -1;
	*prompt = ft_calloc(sizeof(t_pipe), utils.nb_cmd);
	if (!prompt)
		return (1);
	while (++i < utils.nb_cmd)
		(*prompt)[i].cmd = ft_calloc(sizeof(char), (utils.size_cmd[i] + 1));
	i = 0;
	while (i < utils.nb_cmd)
	{
		j = -1;
		while (utils.pipecmd[i][++j])
			(*prompt)[i].cmd[j] = utils.pipecmd[i][j];
		(*prompt)[i].cmd[j] = '\0';
		(*prompt)[i].len_cmd = utils.size_cmd[i];
		i++;
	}
	cmd_struct(utils, prompt);
	found_len_token(utils, prompt);
	set_token(utils, prompt);
	return (0);
}

void	*more_help_cmd_struct(int *nb_cmd, int *len_cmd, t_pipe **prompt)
{
	if (is_redirection((*prompt)[*nb_cmd].cmd[*len_cmd]) == 1)
	{
		*len_cmd += 1;
		if (is_redirection((*prompt)[*nb_cmd].cmd[*len_cmd]) == 1)
			*len_cmd += 1;
		(*prompt)[*nb_cmd].nb_token++;
	}
	while ((*prompt)[*nb_cmd].cmd[*len_cmd] == ' ')
		*len_cmd += 1;
	if ((*prompt)[*nb_cmd].cmd[*len_cmd] && !\
	is_redirection((*prompt)[*nb_cmd].cmd[*len_cmd]) \
	&& (*prompt)[*nb_cmd].cmd[*len_cmd] != '$')
		(*prompt)[*nb_cmd].nb_token++;
}

void	*hcmd_struct(int *nb_cmd, int *len_cmd, \
t_pipe **prompt, int first)
{
	if (*len_cmd > 0 && first == 1)
		(*prompt)[*nb_cmd].nb_token++;
	while ((*prompt)[*nb_cmd].cmd[*len_cmd] && \
	(*prompt)[*nb_cmd].cmd[*len_cmd] != ' '\
	&& (*prompt)[*nb_cmd].cmd[*len_cmd] != '\'' && \
	(*prompt)[*nb_cmd].cmd[*len_cmd] != '\"'\
	&& !is_redirection((*prompt)[*nb_cmd].cmd[*len_cmd]))
		*len_cmd += 1;
}

void	*help_cmd_struct(int nb_cmd, int len_cmd, t_pipe **prompt)
{
	(*prompt)->first = 0;
	while ((*prompt)[nb_cmd].cmd[len_cmd])
	{
		if ((*prompt)[nb_cmd].cmd[len_cmd] == '\'')
		{
			len_cmd++;
			while ((*prompt)[nb_cmd].cmd[len_cmd] != '\'')
				len_cmd++;
			len_cmd++;
		}
		else if ((*prompt)[nb_cmd].cmd[len_cmd] == '\"')
		{
			len_cmd++;
			while ((*prompt)[nb_cmd].cmd[len_cmd] != '\"')
				len_cmd++;
			len_cmd++;
		}
		else if ((is_redirection((*prompt)[nb_cmd].cmd[len_cmd]) \
		== 1) || ((*prompt)[nb_cmd].cmd[len_cmd] == ' '))
			more_help_cmd_struct(&nb_cmd, &len_cmd, prompt);
		else if ((*prompt)[nb_cmd].cmd[len_cmd] == '$')
			hcmd_struct(&nb_cmd, &len_cmd, prompt, (*prompt)->first = 1);
		else
			help_built_struct(&len_cmd, &(*prompt)->first);
	}
}

void	*cmd_struct(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		while ((*prompt)[utils.i].cmd[utils.j] == ' ')
				utils.j++;
		(*prompt)[utils.i].nb_token = 1;
		if (is_redirection((*prompt)[utils.i].cmd[utils.j]) == 1)
		{
			(*prompt)[utils.i].nb_token++;
			while (is_redirection((*prompt)[utils.i].cmd[utils.j]) == 1)
				utils.j++;
			if (!(*prompt)[utils.i].cmd[utils.j])
				(*prompt)[utils.i].nb_token = 1;
		}
		while ((*prompt)[utils.i].cmd[utils.j] == ' ')
				utils.j++;
		help_cmd_struct(utils.i, utils.j, prompt);
		(*prompt)[utils.i].scmd = calloc(sizeof(t_token), \
		((*prompt)[utils.i].nb_token));
		utils.i++;
	}
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
		utils.i++;
}
