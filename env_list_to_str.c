/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:26:29 by wgaspar           #+#    #+#             */
/*   Updated: 2022/07/28 12:28:21 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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
