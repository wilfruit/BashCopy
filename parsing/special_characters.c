/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_characters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:22:42 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 17:22:43 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	len_cmd_pipe(t_manage_pipe *mpipe, char *line)
{
	ft_init_cmdpipe(mpipe);
	while (line[mpipe->i])
	{
		if (line[mpipe->i] == '\'' || line[mpipe->i] == '\"')
		{
			if (len_d_quote(&mpipe->i, mpipe, line) == NULL)
				return (1);
		}
		else if (is_redirection(line[mpipe->i]) == 1)
		{
			if (len_redir(&mpipe->i, mpipe, line) == 1)
				return (1);
		}
		else if (line[mpipe->i] == '|')
			cpt_pipe(&mpipe->i, &mpipe->j, mpipe, line);
		else
		{
			mpipe->size++;
			mpipe->i++;
		}
	}
	mpipe->size_cmd[mpipe->j] = mpipe->size;
	return (0);
}

void	*set_manage(t_manage_pipe *mpipe, char *line)
{	
	int	tmp;

	tmp = -1;
	ft_initsetman(mpipe, line);
	if (mpipe->nb_cmd == 0)
		return (NULL);
	mpipe->size_cmd = ft_calloc(sizeof(int), mpipe->nb_cmd);
	mpipe->pipecmd = ft_calloc(sizeof(char *), mpipe->nb_cmd);
	if (!mpipe->size_cmd || !mpipe->pipecmd)
		return (NULL);
	while (++tmp < mpipe->nb_cmd)
		mpipe->size_cmd[tmp] = 0;
	if (len_cmd_pipe(mpipe, line) == 1)
		return (ft_exit_set_manage(mpipe));
	tmp = -1;
	while (++tmp < mpipe->nb_cmd)
	{
		mpipe->pipecmd[tmp] = ft_calloc(sizeof(char), \
		(mpipe->size_cmd[tmp] + 1));
		if (mpipe->pipecmd[tmp] == NULL)
			return (NULL);
	}
}

void	*make_tab_cmd(t_manage_pipe *mpipe, char *line)
{
	int	l;

	l = 0;
	mpipe->i = 0;
	while (mpipe->i < mpipe->nb_cmd)
	{
		mpipe->j = 0;
		while (mpipe->j < (*mpipe).size_cmd[mpipe->k])
		{
			(*mpipe).pipecmd[mpipe->i][mpipe->j] = line[l];
			mpipe->j++;
			l++;
		}
		l++;
		(*mpipe).pipecmd[mpipe->i][mpipe->j] = '\0';
		mpipe->i++;
		mpipe->k++;
	}
}

void	*all_pipe_cmd(t_manage_pipe *mpipe, char *line)
{
	if ((set_manage(mpipe, line)) == NULL)
		return (NULL);
	add_history(line);
	make_tab_cmd(mpipe, line);
}

void	clean_manage(t_manage_pipe *mpipe, t_pipe **prompt)
{
	int	tmp;

	tmp = -1;
	free(mpipe->size_cmd);
	mpipe->size_cmd = NULL;
	while (++tmp < mpipe->nb_cmd)
	{
		free((mpipe->pipecmd[tmp]));
		mpipe->pipecmd[tmp] = NULL;
	}
	free(mpipe->pipecmd);
	mpipe->pipecmd = NULL;
	free_token(*mpipe, prompt);
	free_struct(*mpipe, prompt);
}
