/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:51:27 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/12 17:56:39 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	replace_oldpwd(t_envi *our_env)
{
	char	*cwd;
	char	*old_pwd;
	t_envi	*current;

	cwd = malloc(sizeof(char) * PATH_MAX);
	current = our_env;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	while (current)
	{
		if (ft_strncmp(current->str, "OLDPWD=", 7) == 0)
		{
			free(current->str);
			current->str = ft_strdup(old_pwd);
		}
		current = current->next;
	}
	free(old_pwd);
	free(cwd);
	return (0);
}

static char	*get_path(int path, t_envi *our_env)
{
	char	*ret;
	t_envi	*env_cpy;

	ret = NULL;
	env_cpy = our_env;
	while (env_cpy)
	{
		if (path == 1 && ft_strncmp(env_cpy->str, "HOME=", 5) == 0)
		{
			ret = ft_strdup(env_cpy->str + 5);
			return (ret);
		}
		if (path == 2 && ft_strncmp(env_cpy->str, "OLDPWD=", 7) == 0)
		{
			ret = ft_strdup(env_cpy->str + 7);
			return (ret);
		}
		env_cpy = env_cpy->next;
	}
	return ("not_set");
}

static int	go_home(char **cmd, t_envi *our_env)
{
	char	*home_path;

	home_path = NULL;
	home_path = get_path(1, our_env);
	if (!home_path)
		return (1);
	if (ft_strncmp(home_path, "not_set", ft_strlen("not_set") == 0))
	{
		free(home_path);
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	replace_oldpwd(our_env);
	chdir(home_path);
	free(home_path);
	return (0);
}

static int	go_back_to_oldpwd(char **cmd, t_envi *our_env)
{
	char	*pwd;
	char	*old_pwd;

	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	old_pwd = NULL;
	getcwd(pwd, sizeof(pwd));
	old_pwd = get_path(2, our_env);
	if (ft_strncmp(old_pwd, "not_set", ft_strlen("not_set") == 0))
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		free(pwd);
		free(old_pwd);
		return (1);
	}
	replace_oldpwd(our_env);
	chdir(old_pwd);
	free(pwd);
	free(old_pwd);
	return (0);
}

int	my_cd(char **cmd, t_envi *our_env)
{
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if ((cmd && cmd[1]) && ft_strncmp(cmd[1], "-", ft_strlen(cmd[1])) == 0)
		return (go_back_to_oldpwd(cmd, our_env));
	if ((cmd && cmd[0] && !cmd[1]) \
	|| (cmd && ft_strncmp(cmd[1], "~", ft_strlen(cmd[1])) == 0) \
	|| (cmd && ft_strncmp(cmd[1], "--", ft_strlen(cmd[1])) == 0))
		return (go_home(cmd, our_env));
	else
	{
		replace_oldpwd(our_env);
		if (chdir(cmd[1]) == 0)
			set_newpwd(cmd[1], our_env);
		else
			return (error_cd(cmd));
	}
	return (0);
}