/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:56:21 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 16:51:36 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	print_error_name(char *cmd)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

static void	add_or_update_env(t_envi *env, t_envi *exp, char *arg)
{
	t_envi	*temp;
	char	**av;

	av = ft_split(arg, '=');
	av[0] = ft_strjoinmod(av[0], "=");
	temp = env;
	if (!is_in_such_list(env, av[0]))
	{
		ft_free_chr(av);
		return (add_node_to_env(env, arg));
	}
	while (temp && is_in_such_list(env, av[0]))
	{
		if (ft_strncmp(temp->str, arg, ft_strlen(av[0])) == 0)
		{
			free(temp->str);
			temp->str = ft_strdup(arg);
			ft_free_chr(av);
			temp = NULL;
			return ;
		}
		temp = temp->next;
	}
	ft_free_chr(av);
}

static void	not_in_such_utils(char **av, t_envi *exp, char *arg)
{
	add_node_to_exp(exp, arg);
	ft_free_chr(av);
	return ;
}

static void	add_or_update_exp(t_envi *env, t_envi *exp, char *arg)
{
	t_ext	d;

	if (ft_strchr(arg, '='))
		d.av = ft_split(arg, '=');
	else
		d.av = no_assign_export(arg);
	d.temp = exp;
	if (!is_in_such_list(exp, d.av[0]))
		return (not_in_such_utils(d.av, exp, arg));
	while (d.temp && is_in_such_list(exp, d.av[0]))
	{
		if (ft_strncmp(d.temp->str, arg, ft_strlen(d.av[0])) == 0)
		{
			if (!(!ft_strchr(arg, '=')))
			{
				free(d.temp->str);
				d.temp->str = ft_strdup(arg);
			}
			ft_free_chr(d.av);
			d.temp = NULL;
			return ;
		}
		d.temp = d.temp->next;
	}
	ft_free_chr(d.av);
}

int	my_export(char **cmd, t_envi *env, t_envi *exports)
{
	int	i;

	i = 1;
	if (cmd && !cmd[1])
		my_exprint(exports);
	if (cmd && cmd[1])
	{
		while (cmd[i])
		{
			if (is_valid_identifier_exp(cmd[i]) == 0 && \
			ft_strchr(cmd[i], 61) != NULL)
			{
				add_or_update_env(env, exports, cmd[i]);
				add_or_update_exp(env, exports, cmd[i]);
			}
			else if (is_valid_identifier(cmd[i]) == 0 && \
			!ft_strchr(cmd[i], '='))
				add_or_update_exp(env, exports, cmd[i]);
			else
				return (print_error_name(cmd[i]));
			i++;
		}
	}
	return (0);
}
