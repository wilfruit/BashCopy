/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:55:03 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 16:47:36 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	error_cd(char **cmd)
{
	ft_putstr_fd("minishell: cd : ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

void	set_newpwd(char *path, t_envi *our_env)
{
	char	*cwd;
	char	*new_pwd;
	t_envi	*current;

	cwd = malloc(sizeof(char) * PATH_MAX);
	current = our_env;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	new_pwd = ft_strjoin("PWD=", cwd);
	while (current)
	{
		if (ft_strncmp(current->str, "PWD=", 4) == 0)
		{
			free(current->str);
			current->str = ft_strdup(new_pwd);
		}
		current = current->next;
	}
	free(new_pwd);
	free(cwd);
}
