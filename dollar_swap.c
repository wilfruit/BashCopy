/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:24:07 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/02 12:10:49 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	dollar_count(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			n++;
		i++;
	}
	return (n);
}

/* static char	*get_macro(t_shell *shpack, char *str)
{
	t_envi	*copy;
	char	*macro;
	char	*ret;

	ret = NULL;
	copy = shpack->our_env;
	if (str[0] == '$')
		macro = ft_strdup(str + 1);
	else
		macro = ft_strdup(str);
	macro = ft_strjoin(macro, "=");
	while (copy)
	{
		if (ft_strncmp(copy->str, macro, ft_strlen(macro)) == 0)
		{
			ret = ft_strdup(copy->str + ft_strlen(macro));
			free(macro);
			free(str);
			return (ret);
		}
		copy = copy->next;
	}
	free(macro);
	free(str);
	return (NULL);
} */

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

/* static char	*get_macro(t_shell *shpack, char *str)
{
	t_envi	*copy;
	char	*macro;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
 	macro = (char *)malloc(sizeof(char));
	macro[0] = '\0';
//	macro = NULL;
	copy = shpack->our_env;
	if (str[0] == '$')
		macro = ft_strjoin(macro, str + 1);
	else
		macro = ft_strjoin(macro, str);
	macro = ft_strjoin(macro, "=");
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
} */

static char	*dollar_deluxe(t_shell *shpack, char *str)
{
	char	*ret;
	char	**split;
	int		i;
	int		n;

/*  	ret = malloc(sizeof(char));
	ret[0] = '\0'; */
	ret = NULL;
	n = 0;
	i = 0;
	split = ft_split(str, '$');
	if (!split[0] && str[0] == '$')
	{
		free(str);
		free(ret);
		ft_free_chr(split);
		return (ft_strdup("89669"));
	}
	if (str[0] != '$')
	{
		ret = ft_strjoin(ret, split[0]);
		i++;
		n++;
	}
	while (i < dollar_count(str) + n)
	{
		if (split[i] == NULL)
			ret = ft_strjoin(ret, "89669");
		else if (ft_strncmp(split[i], "?", ft_strlen(split[i])) == 0)
			ret = ft_strjoin(ret, ft_itoa(shpack->error_ret));
		else
		{
			if (get_macro(shpack, split[i]))
				ret = ft_strjoin(ret, get_macro(shpack, split[i]));
		}
		i++;
	}
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