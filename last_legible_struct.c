#include "mini_shell.h"

void	*first_help_len_token(int *i, int *j, int *k, t_pipe **prompt)
{
	while ((*prompt)[*i].cmd[*j] == ' ')
		*j += 1;
	if ((*prompt)[*i].cmd[*j] != '\0')
		(*prompt)[*i].scmd[*k].len_value = 0;
	if (is_redirection((*prompt)[*i].cmd[*j]))
	{
		while (is_redirection((*prompt)[*i].cmd[*j]))
		{
			(*prompt)[*i].scmd[*k].len_value += 1;
			*j += 1;
		}
		if ((*prompt)[*i].cmd[*j] != ' ')
			*k += 1;
	}
	if (((*prompt)[*i].cmd[*j] == '$'))
	{
		(*prompt)[*i].scmd[*k].len_value += 1;
		*j += 1;
	}
}

void	*last_help_len_token(int *i, int *j, int *k, t_pipe **prompt)
{
	if ((*prompt)[*i].cmd[*j] == '\'')
	{
		*j += 1;
		while ((*prompt)[*i].cmd[*j] != '\'')
		{
			(*prompt)[*i].scmd[*k].len_value += 1;
			*j += 1;
		}
		*j += 1;
	}
	if ((*prompt)[*i].cmd[*j] == '\"')
	{
		*j += 1;
		while ((*prompt)[*i].cmd[*j] != '\"')
		{
			(*prompt)[*i].scmd[*k].len_value += 1;
			*j += 1;
		}
		*j += 1;
	}
	if ((*prompt)[*i].cmd[*j] && (*prompt)[*i].cmd[*j] != ' ' \
	&& (*prompt)[*i].cmd[*j] != '\'' && (*prompt)[*i].cmd[*j] != '\"')
	{
		(*prompt)[*i].scmd[*k].len_value += 1;
		*j += 1;
	}
}

void	*found_len_token(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		utils.k = 0;
		while ((*prompt)[utils.i].cmd[utils.j])
		{
			first_help_len_token(&utils.i, &utils.j, &utils.k, prompt);
			while (((*prompt)[utils.i].cmd[utils.j] && \
			(*prompt)[utils.i].cmd[utils.j] != ' ') && \
			(utils.k < (*prompt)[utils.i].nb_token) && \
			!is_redirection((*prompt)[utils.i].cmd[utils.j]))
				last_help_len_token(&utils.i, &utils.j, &utils.k, prompt);
			utils.k++;
		}
		utils.i++;
	}
}
