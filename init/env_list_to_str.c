/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:26:29 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 01:40:25 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	fake_here_doc(t_exec_single *data, char *lim)
{
	pid_t	child;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	child = fork();
	if (child < 0)
		return ;
	if (child == 0)
	{
		signal(SIGINT, sig_zigma);
		fake_child_doc(lim);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(child, NULL, 0);
	}
}

static int	count_nodes(t_envi	*env)
{
	t_envi	*counter;
	int		count;

	count = 0;
	counter = env;
	if (counter)
	{
		count++;
		counter = counter->next;
	}
	else
		return (0);
	while (counter)
	{
		counter = counter->next;
		count++;
	}
	return (count);
}

char	**charize_env(t_envi	*env)
{
	char	**ret;
	t_envi	*temp;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (count_nodes(env) + 1));
	if (!ret)
		return (NULL);
	temp = env;
	while (temp)
	{
		if (!ret)
			perror("malloc : ");
		ret[i] = ft_strdup(temp->str);
		temp = temp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
