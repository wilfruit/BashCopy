/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:59:10 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/02 11:37:52 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int				glob = 0;

void	print_linked_list(t_envi *our_env)
{
	while (our_env)
	{
		printf("%s\n", our_env->str);
		our_env = our_env->next;
	}
}

static void	create_minimum_data(t_shell *data, char **env)
{
	t_envi	*temp;
	t_envi	*cursor;

	cursor = ft_calloc(sizeof(t_envi), 1);
	cursor->str = ft_strdup("heyarnold\n");
	cursor->next = NULL;
	data->our_env = cursor;
	data->exports = cursor;
	cursor->str = ft_strdup("PWD=");
	temp = ft_calloc(sizeof(t_envi), 1);
	temp->str = ft_strdup("OLDPWD=");
	temp->next = NULL;
	cursor->next = temp;
	cursor = temp;
	temp = ft_calloc(sizeof(t_envi), 1);
	temp->str = ft_strdup("PATH=");
	temp->next = NULL;
	cursor->next = temp;
	cursor = temp;
	return ;
}

static void	shell_pack_init(t_shell *data, char **env)
{
	data->error_ret = 0;
	data->exit_switch = 0;
	data->exit_ret = 0;
 	if (env[0])
	{
		download_env_one(data, env);
		download_env_two(data, env);
 	}
 	else
		create_minimum_data(data, env);
}

static int	sig_used(int error_ret)
{
	if (glob == 130)
	{
		glob = 0;
		return (130);
	}
	else
		return (error_ret);
}

int	main(int argc, char **argv, char **env)
{
 	char			*line;
	char			*path;
	t_shell			shell_pack;

	shell_pack_init(&shell_pack, env);
 	shell_pack.exit_switch = 0;
	control(&shell_pack);
	line = NULL;
	while (shell_pack.exit_switch == 0)
	{
		if (shell_pack.error_ret == 0)
			line = readline("\e[1;32mmshell> \e[0m");
		else
			line = readline("\e[1;31mmshell> \e[0m");
 		if (check_line(&line) == NULL)
			exit(0);
		if (all_pipe_cmd(&shell_pack.mpipe, line) != NULL)
		{
			shell_pack.error_ret = sig_used(shell_pack.error_ret);
			set_struct(&line, shell_pack.mpipe, &shell_pack.token);
			shell_pack.nb_cell = shell_pack.mpipe.nb_cmd;
	 		if (shell_pack.mpipe.size != 0)
				minishell_operator(&shell_pack);
			clean_manage(&shell_pack.mpipe, &shell_pack.token);
		}
		free(line);
		shell_pack.error_ret = sig_used(shell_pack.error_ret);
	}
	ft_free_env(shell_pack.our_env);
	ft_free_env(shell_pack.exports);
	return (shell_pack.exit_ret);
}

/* Leaks chelou avec charize env ??????? incomprehensible
Initialized value ?
ls | pwd           -> encore un probleme
quand je fais un pipe puis une commande normale (genre "hey")
et invalid syntax */

/* mshell> export A=" -la"
mshell> ls$A      => ça crash*/

// si jamais on utilise un control-d apres un control-c ca bloque

// checker les invalidites pour "fjweijpowjopvwrj$D"