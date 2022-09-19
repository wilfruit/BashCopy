/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:17:54 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 02:19:13 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	outfile_not_a(t_exec_single *pack, int cell_nb, t_shell *data, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(data->token[cell_nb].scmd[i + 1].value, 2);
	ft_putendl_fd(" : Permission denied", 2);
	data->error_ret = 1;
	return (1);
}

int	treat_redir_out(t_shell *data, t_exec_single *pack, int cell_nb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((data->token[cell_nb].scmd[i].type != 2 \
	&& data->token[cell_nb].scmd[i].type != 3) \
	&& i < data->token[cell_nb].nb_token)
		i++;
	while (j < pack->nb_redirout)
	{
		if (data->token[cell_nb].scmd[i].type == 2 \
		&& (i + 1) < data->token[cell_nb].nb_token)
			pack->redirout = \
open(data->token[cell_nb].scmd[i + 1].value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->token[cell_nb].scmd[i].type == 3 && (i + 1) < data->token[cell_nb].nb_token)
			pack->redirout = \
open(data->token[cell_nb].scmd[i + 1].value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (pack->redirout == -1)
			return (outfile_not_a(pack, cell_nb, data, i));
		if ((data->token[cell_nb].scmd[i].type == 2 || data->token[cell_nb].scmd[i].type == 3) && !((i + 1) < data->token[cell_nb].nb_token))
			data->error_ret = ft_syntax_error();
		i += 2;
		j++;
	}
	return (0);
}

static int	infile_not_allowed(t_exec_single *pack, int cell_nb, t_shell *data, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(data->token[cell_nb].scmd[i + 1].value, 2);
	ft_putendl_fd(" Permission denied", 2);
	data->error_ret = 1;
	return (1);
}

static int	infile_not_real(t_exec_single *pack, int cell_nb, t_shell *data, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(data->token[cell_nb].scmd[i + 1].value, 2);
	ft_putendl_fd(" No such file or directory", 2);
	data->error_ret = 1;
	return (1);
}
// Tester avant d'effacer ce message


int	treat_redir_in(t_shell *data, t_exec_single *pack, int cell_nb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[cell_nb].scmd[i].type != 4 \
	&& i < data->token[cell_nb].nb_token)
		i++;
	while (j < pack->nb_redirin)
	{
		if (data->token[cell_nb].scmd[i].type == 4 \
		&& ((i + 1) < data->token[cell_nb].nb_token))
		{
			if (access(data->token[cell_nb].scmd[i + 1].value, R_OK) != 0 && \
			access(data->token[cell_nb].scmd[i +1].value, F_OK) == 0)
				return (infile_not_allowed(pack, cell_nb, data, i));
			if (access(data->token[cell_nb].scmd[i + 1].value, F_OK) != 0)
				return (infile_not_real(pack, cell_nb, data, i));
			pack->redirin = \
open(data->token[cell_nb].scmd[i + 1].value, O_RDONLY);
		}
		if (data->token[cell_nb].scmd[i].type == 4 \
		&& !((i + 1) < data->token[cell_nb].nb_token))
			data->error_ret = ft_syntax_error();
		i += 2;
		j++;
	}
	return (0);
}

/* bash-3.2$ < wr ls
bash: wr: No such file or directory
bash-3.2$ mdir wrrr
bash: mdir: command not found
bash-3.2$ mkdir vrrr
bash-3.2$ < wr < wrrr ls
bash: wr: No such file or directory
bash-3.2$ < wrr ls
bash: wrr: Permission denied
bash-3.2$ echo $?
1
bash-3.2$ < wrr ls
bash: wrr: Permission denied
bash-3.2$ < wr < wrrr ls
bash: wr: No such file or directory
bash-3.2$ echo $?
1  pour le multi aussi*/
