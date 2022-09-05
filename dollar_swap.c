/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:24:07 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/05 17:34:35 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*get_macro(t_shell *shpack, char *str)
{
	t_macro	data;

	data.i = 0;
	data.ret = NULL;
	data.copy = shpack->our_env;
	if (str[0] == '$')
		data.macro = ft_strdup(str + 1);
	else
		data.macro = ft_strdup(str);
	data.macro = ft_strjoinmod(data.macro, "=");
	data.i = ft_strlen(data.macro);
	while (data.copy)
	{
		if (ft_strncmp(data.copy->str, data.macro, data.i) == 0)
		{
			data.ret = ft_strdup(data.copy->str + data.i);
			free(data.macro);
			free(str);
			return (data.ret);
		}
		data.copy = data.copy->next;
	}
	free(data.macro);
	free(str);
	return (NULL);
}

char	*build_dollar_return(t_shell *shpack, char **split, char *str, int i)
{
	char	*ret;
	int		n;

	n = 0;
	ret = NULL;
	if (str[0] != '$')
	{
		ret = ft_strjoinmod(ret, split[0]);
		i++;
		n++;
	}
	while (i < dollar_count(str) + n)
	{
		if (split[i] == NULL)
			ret = ft_strjoinmod(ret, "89669");
		else if (ft_strncmp(split[i], "?", ft_strlen(split[i])) == 0)
			ret = ft_strjoinmod(ret, ft_itoa(shpack->error_ret));
		else
		{
			if (get_macro(shpack, ft_strdup(split[i])))
				ret = \
				ft_strjoinmod(ret, get_macro(shpack, ft_strdup(split[i])));
		}
		i++;
	}
	return (ret);
}

char	*dollar_deluxe(t_shell *shpack, char *str)
{
	char	*ret;
	char	**split;
	int		i;

	ret = NULL;
	i = 0;
	split = ft_split(str, '$');
	if (!split[0] && str[0] == '$')
		return (quit_dollar_deluxe(str, ret, split));
	ret = build_dollar_return(shpack, split, str, i);
	ft_free_chr(split);
	return (ret);
}

char	*dollar_swap(t_shell *shpack, char *str)
{
	if (dollar_count(str) > 1 && (str[0] == '$'))
		return (dollar_deluxe(shpack, str));
	else if (ft_strncmp(str, "$", ft_strlen(str)) == 0)
		return (str);
	else if (ft_strncmp(str, "$?", ft_strlen(str)) == 0)
		return (ft_itoa(shpack->error_ret));
	else if (str[0] != '$')
		return (dollar_deluxe(shpack, str));
	else
		return (get_macro(shpack, str));
}
