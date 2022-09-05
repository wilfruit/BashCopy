/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legible_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:13:52 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/05 18:13:53 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "mini_shell.h"

void	*malloc_set_token(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = -1;
	while (++utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		while (utils.j < (*prompt)[utils.i].nb_token)
		{
			(*prompt)[utils.i].scmd[utils.j].value = \
			ft_calloc(sizeof(char), ((*prompt) \
			[utils.i].scmd[utils.j].len_value + 1));
			utils.j++;
		}
	}
}

void	*first_help_set_token(t_manage_pipe *data, int *v, t_pipe **prompt)
{
	*v = 0;
	while ((*prompt)[data->i].cmd[data->j] == ' ')
		data->j += 1;
	if (is_redirection((*prompt)[data->i].cmd[data->j]))
	{
		while (is_redirection((*prompt)[data->i].cmd[data->j]))
		{
			(*prompt)[data->i].scmd[data->k].value[*v] \
			= (*prompt)[data->i].cmd[data->j];
			data->j += 1;
			*v += 1;
		}
		if ((*prompt)[data->i].cmd[data->j] != ' ')
		{
			data->k += 1;
			*v = 0;
		}
	}
	if ((*prompt)[data->i].cmd[data->j] == '$')
	{
		(*prompt)[data->i].scmd[data->k].is_dollar = DOLLAR_MACRO;
		(*prompt)[data->i].scmd[data->k].value[*v] \
		= (*prompt)[data->i].cmd[data->j];
		data->j += 1;
		*v += 1;
	}	
}

void	*last_help_set_token(t_manage_pipe *data, int *v, t_pipe **prompt)
{
	if ((*prompt)[data->i].cmd[data->j] == '\'')
	{
		data->j += 1;
		while ((*prompt)[data->i].cmd[data->j] != '\'')
		{
			(*prompt)[data->i].scmd[data->k].value[*v] \
			= (*prompt)[data->i].cmd[data->j];
			if ((*prompt)[data->i].cmd[data->j] == '$')
				(*prompt)[data->i].scmd[data->k].is_dollar = DOLLAR_NO;
			*v += 1;
			data->j += 1;
		}
		data->j += 1;
	}
	if ((*prompt)[data->i].cmd[data->j] == '\"')
	{
		data->j += 1;
		while ((*prompt)[data->i].cmd[data->j] != '\"')
		{
			(*prompt)[data->i].scmd[data->k].value[*v] \
			= (*prompt)[data->i].cmd[data->j];
			if ((*prompt)[data->i].cmd[data->j] == '$')
				(*prompt)[data->i].scmd[data->k].is_dollar = DOLLAR_MACRO;
			*v += 1;
			data->j += 1;
		}
		data->j += 1;
	}	
}

void	*last_more_help_set_token(t_manage_pipe *data, int *v, t_pipe **prompt)
{
	if ((*prompt)[data->i].cmd[data->j] == '$')
		(*prompt)[data->i].scmd[data->k].is_dollar = DOLLAR_MACRO;
	(*prompt)[data->i].scmd[data->k].value[*v] \
	= (*prompt)[data->i].cmd[data->j];
	data->j += 1;
	*v += 1;
}

void	*set_token(t_manage_pipe utils, t_pipe **prompt)
{
	int	v;

	malloc_set_token(utils, prompt);
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		utils.k = 0;
		while ((*prompt)[utils.i].cmd[utils.j])
		{
			first_help_set_token(&utils, &v, prompt);
			while (((*prompt)[utils.i].cmd[utils.j] && \
			(*prompt)[utils.i].cmd[utils.j] != ' ') && \
			(utils.k < (*prompt)[utils.i].nb_token) && \
			!is_redirection((*prompt)[utils.i].cmd[utils.j]))
			{	
				last_help_set_token(&utils, &v, prompt);
				if (((*prompt)[utils.i].cmd[utils.j] != '\0') && \
				(*prompt)[utils.i].cmd[utils.j] != ' ' \
				&& ((*prompt)[utils.i].cmd[utils.j] != '\'') \
				&& ((*prompt)[utils.i].cmd[utils.j] != '"'))
					last_more_help_set_token(&utils, &v, prompt);
			}
			utils.k++;
		}
		determine_type(&(*prompt)[utils.i], -1);
		utils.i++;
	}
}
 */

 #include "mini_shell.h"

void	*malloc_set_token(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = -1;
	while (++utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		while (utils.j < (*prompt)[utils.i].nb_token)
		{
		//	printf("size_token :%d\n", prompt[utils.i]->scmd[utils.j].len_value);
			(*prompt)[utils.i].scmd[utils.j].value = \
			ft_calloc(sizeof(char), ((*prompt) \
			[utils.i].scmd[utils.j].len_value + 1));
			utils.j++;
		//	(*prompt)[utils.i].scmd[utils.j].value[((*prompt)[utils.i].scmd[utils.j].len_value + 1)] = '\0';
		}
	}
}

void	*first_help_set_token(int *i, int *j, int *k, int *v, t_pipe **prompt)
{
	*v = 0;
	while ((*prompt)[*i].cmd[*j] == ' ')
		*j += 1;
	if (is_redirection((*prompt)[*i].cmd[*j]))
	{
		while (is_redirection((*prompt)[*i].cmd[*j]))
		{
			(*prompt)[*i].scmd[*k].value[*v] = (*prompt)[*i].cmd[*j];
			*j += 1;
			*v += 1;
		}
		if ((*prompt)[*i].cmd[*j] != ' ')
		{
			*k += 1;
			*v = 0;
		}
	}
	if ((*prompt)[*i].cmd[*j] == '$')
	{
		(*prompt)[*i].scmd[*k].is_dollar = DOLLAR_MACRO;
		(*prompt)[*i].scmd[*k].value[*v] = (*prompt)[*i].cmd[*j];
		*j += 1;
		*v += 1;
	}	
}

void	*last_help_set_token(int *i, int *j, int *k, int *v, t_pipe **prompt)
{
	if ((*prompt)[*i].cmd[*j] == '\'')
	{
		*j += 1;
		while ((*prompt)[*i].cmd[*j] != '\'')
		{
			(*prompt)[*i].scmd[*k].value[*v] = (*prompt)[*i].cmd[*j];
			printf("CP : %c\n", (*prompt)[*i].cmd[*j]);
			if ((*prompt)[*i].cmd[*j] == '$')
				(*prompt)[*i].scmd[*k].is_dollar = DOLLAR_NO;
			*v += 1;
			*j += 1;
		}
		*j += 1;
	}
	if ((*prompt)[*i].cmd[*j] == '\"')
	{
		*j += 1;
		while ((*prompt)[*i].cmd[*j] != '\"')
		{
			(*prompt)[*i].scmd[*k].value[*v] = (*prompt)[*i].cmd[*j];
			if ((*prompt)[*i].cmd[*j] == '$')
				(*prompt)[*i].scmd[*k].is_dollar = DOLLAR_MACRO;
			*v += 1;
			*j += 1;
		}
		*j += 1;
	}	
}

void	*last_more_help_set_token(int *i, int *j, int *k, int *v, t_pipe **prompt)
{
	if ((*prompt)[*i].cmd[*j] == '$')
		(*prompt)[*i].scmd[*k].is_dollar = DOLLAR_MACRO;
	(*prompt)[*i].scmd[*k].value[*v] = (*prompt)[*i].cmd[*j];
	*j += 1;
	*v += 1;
}

void	*set_token(t_manage_pipe utils, t_pipe **prompt)
{
	int	v;

	malloc_set_token(utils, prompt);
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		utils.k = 0;
		while ((*prompt)[utils.i].cmd[utils.j])
		{
			first_help_set_token(&utils.i, &utils.j, &utils.k, &v, prompt);
			while (((*prompt)[utils.i].cmd[utils.j] && \
			(*prompt)[utils.i].cmd[utils.j] != ' ') && \
			(utils.k < (*prompt)[utils.i].nb_token) && \
			!is_redirection((*prompt)[utils.i].cmd[utils.j]))// \
			&& ((*prompt)[utils.i].cmd[utils.j] != '$'))
			{	
				last_help_set_token(&utils.i, &utils.j, &utils.k, &v, prompt);
				if (((*prompt)[utils.i].cmd[utils.j] != '\0') && \
				(*prompt)[utils.i].cmd[utils.j] != ' ' && ((*prompt)[utils.i].cmd[utils.j] != '\'') && ((*prompt)[utils.i].cmd[utils.j] != '"'))
					last_more_help_set_token(&utils.i, &utils.j, \
					&utils.k, &v, prompt);
			}
			utils.k++;
		}
		determine_type(&(*prompt)[utils.i]);
		utils.i++;
	}
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.k = 0;
		/* printf("commande[%d]\n", utils.i);
		printf("-------------------------------------------------\n"); */
		while (utils.k < (*prompt)[utils.i].nb_token)
		{
		/* 	printf("token[%d] : %s\n",utils.k, (*prompt)[utils.i].scmd[utils.k].value);
			printf("is_dollar : %d\n", (*prompt)[utils.i].scmd[utils.k].is_dollar); */
			utils.k++;
		}
		/* printf("-------------------------------------------------\n");
		printf("\n\n"); */
		utils.i++;
	} 
}
