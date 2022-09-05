/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:24:07 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/05 14:00:53 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*get_macro(t_shell *shpack, char *str)
{
	t_envi	*copy;
	char	*macro;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	copy = shpack->our_env;
	if (str[0] == '$')
		macro = ft_strdup(str + 1);
	else
		macro = ft_strdup(str);
	macro = ft_strjoinmod(macro, "=");
 	i = ft_strlen(macro);
 	while (copy)
	{
		if (ft_strncmp(copy->str, macro, i) == 0)
		{
			ret = ft_strdup(copy->str + i);
			free(macro);
			free(str);
			return (ret);
		}
		copy = copy->next;
	}
	free(macro);
	free(str);
	return (NULL);
}

static char	*quit_dollar_deluxe(char *str, char *ret, char **split)
{
	free(str);
	free(ret);
	ft_free_chr(split);
	return (ft_strdup("89669"));
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
				ret = ft_strjoinmod(ret, get_macro(shpack, ft_strdup(split[i])));
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
		return(ft_itoa(shpack->error_ret));
	else if (str[0] != '$')
		return(dollar_deluxe(shpack, str));
	else
		return(get_macro(shpack, str));
}