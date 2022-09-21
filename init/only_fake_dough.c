/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_fake_dough.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:44:58 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/21 16:44:59 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	init_box(t_dolret *box)
{
	box->n = 0;
	box->ret = NULL;
	box->itoa = NULL;
	box->ptr = NULL;
}

static char	*ft_joinedtwo(char *s1, char *s2, char *sjoined)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[j])
	{
		sjoined[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		sjoined[i] = s2[j];
		i++;
		j++;
	}
	sjoined[i] = '\0';
	free (s1);
	free (s2);
	return (sjoined);
}

char	*ft_strjoinmodtwo(char *s1, char *s2)
{
	char	*sjoined;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	sjoined = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!sjoined)
		return (NULL);
	return (sjoined = ft_joinedtwo(s1, s2, sjoined));
}

void	create_minimum_data(t_shell *data, char **env)
{
	t_envi	*temp;
	t_envi	*cursor;

	cursor = ft_calloc(sizeof(t_envi), 1);
	cursor->str = ft_strdup("heyarnold\n");
	cursor->next = NULL;
	data->our_env = cursor;
	data->exports = cursor;
	cursor->str = ft_strdup("PWD=");
	temp = ft_calloc(sizeof(t_envi), 1);
	temp->str = ft_strdup("OLDPWD=");
	temp->next = NULL;
	cursor->next = temp;
	cursor = temp;
	temp = ft_calloc(sizeof(t_envi), 1);
	temp->str = ft_strdup("PATH=");
	temp->next = NULL;
	cursor->next = temp;
	cursor = temp;
	return ;
}

int	has_only_monopoly_dollars(t_shell *data, int num)
{
	int		i;
	int		val;
	char	*str;

	i = 0;
	val = 0;
	str = NULL;
	while (i < data->token[num].nb_token)
	{
		str = dollar_swap(data, ft_strdup(data->token[num].scmd[i].value));
		if ((data->token[num].scmd[i].is_dollar == 1 \
		&& str == NULL))
			i++;
		else
		{
			free(str);
			return (0);
		}
		free(str);
	}
	data->error_ret = 0;
	return (1);
}
