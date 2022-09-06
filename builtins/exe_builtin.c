/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:29:24 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 01:38:42 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	ft_fill_builtin_tab(char **tab)
{
	tab[0] = ft_strdup("echo");
	tab[1] = ft_strdup("cd");
	tab[2] = ft_strdup("pwd");
	tab[3] = ft_strdup("export");
	tab[4] = ft_strdup("unset");
	tab[5] = ft_strdup("env");
	tab[6] = ft_strdup("exit");
	tab[7] = NULL;
}

int	ft_is_built_in(char *cmd)
{
	char	**built_tab;
	int		i;

	i = 0;
	built_tab = (char **)malloc(sizeof(char *) * 8);
	if (!built_tab)
		perror("malloc :");
	ft_fill_builtin_tab(built_tab);
	while (built_tab[i] != NULL && cmd)
	{
		if (ft_strncmp(cmd, built_tab[i], ft_strlen(built_tab[i])) == 0)
		{
			ft_free_chr(built_tab);
			return (1);
		}
		i++;
	}
	ft_free_chr(built_tab);
	return (0);
}

void	ft_exec_built_in(t_shell *data, char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", ft_strlen("echo")))
		data->error_ret = my_echo(cmd);
	if (!ft_strncmp(cmd[0], "cd", ft_strlen("cd")))
		data->error_ret = my_cd(cmd, data->our_env);
	if (!strncmp(cmd[0], "pwd", ft_strlen("pwd")))
		data->error_ret = my_pwd(cmd);
	if (!strncmp(cmd[0], "export", ft_strlen("export")))
		data->error_ret = my_export(cmd, data->our_env, data->exports);
	if (!strncmp(cmd[0], "unset", ft_strlen("unset")))
		data->error_ret = my_unset(cmd, data);
	if (!strncmp(cmd[0], "env", ft_strlen("env")))
		data->error_ret = my_env(data->our_env, cmd);
	if (!strncmp(cmd[0], "exit", ft_strlen("exit")))
		data->error_ret = my_exit(cmd, data);
	if (cmd)
		ft_free_chr(cmd);
	if (data->nb_cell > 1)
		exit (data->error_ret);
}
