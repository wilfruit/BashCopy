/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:51:00 by wgaspar           #+#    #+#             */
/*   Updated: 2022/08/31 16:51:06 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	find_and_unset_node_exp(t_shell *pack, char *arg)
{
	t_envi	*temp;
	t_envi	*prev;
	char	*vari;

	temp = pack->exports;
	vari = ft_strdup(arg);
	if (temp && ft_strncmp(temp->str, vari, ft_strlen(temp->str)) == 0)
	{
		pack->exports = temp->next;
		ft_memdel(temp->str);
		ft_memdel(temp);
		free(vari);
		return ;
	}
	while (temp && ft_strncmp(temp->str, vari, ft_strlen(vari)))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
	{
		free(vari);
		return ;
	}
	prev->next = temp->next;
	free(vari);
	free(temp);
}

static void	find_and_unset_node_env(t_shell *pack, char *arg)
{
	t_envi	*temp;
	t_envi	*prev;
	char	*vari;

	temp = pack->our_env;
	vari = ft_strjoin(arg, "=");
	if (temp && ft_strncmp(temp->str, vari, ft_strlen(vari)) == 0)
	{
		pack->our_env = temp->next;
		ft_memdel(temp->str);
		ft_memdel(temp);
		free(vari);
		return ;
	}
	while (temp && ft_strncmp(temp->str, vari, ft_strlen(vari)))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
	{
		free(vari);
		return ;
	}
	prev->next = temp->next;
	free(vari);
	free(temp);
}

int	is_valid_identifier(char *cmd)
{
	int	al_or_undersc;
	int	i;

	al_or_undersc = 0;
	i = 0;
	while (cmd[i])
	{
		if (ft_isalpha(cmd[i]) || ft_strncmp(&cmd[i], "_", 1) == 0)
			al_or_undersc++;
		if (!ft_isalnum(cmd[i]) && ft_strncmp(&cmd[i], "_", 1) != 0)
			return (-1);
		i++;
	}
	if (al_or_undersc > 0)
		return (0);
	else
		return (-1);
}

int	my_unset(char **cmd, t_shell *pack)
{
	int	i;

	i = 1;
	if (cmd && !cmd[1])
		return (0);
	if (cmd && cmd[1])
	{
		while(cmd[i])
		{
			if (is_valid_identifier(cmd[i]) == 0)
			{
				find_and_unset_node_env(pack, cmd[i]);
				find_and_unset_node_exp(pack, cmd[i]);
			}
			else
			{
				ft_putstr_fd("minishell: unset: `", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putendl_fd("': not a valid identifier", 2);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
