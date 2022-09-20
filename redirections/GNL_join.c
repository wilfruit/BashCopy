/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GNL_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:32:47 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/20 15:32:08 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	maxi_free(t_shell *data)
{
	clean_manage(&data->mpipe, &data->token);
	ft_free_env(data->our_env);
	ft_free_env(data->exports);
}

void	spec_free(t_shell *data, t_exec_single *pack)
{
	if (pack->cmdargs &&\
	pack->cmdargs[0] && !ft_is_built_in(pack->cmdargs[0]))
		ft_free_chr(pack->allpaths);
	if (pack->cmdargs &&\
	pack->cmdargs[0] && !ft_is_built_in(pack->cmdargs[0]))
		free(pack->cmdstat);
	ft_free_chr(pack->cmdargs);
}

void	spec_free_m(t_shell *data, t_exec_multi *pack)
{
	ft_free_chr(pack->allpaths);
	if (pack->cmdargs &&\
	pack->cmdargs[0] && !ft_is_built_in(pack->cmdargs[0]))
		free(pack->cmdstat);
	ft_free_chr(pack->cmdargs);
}

static char	*ft_joined(char *s1, char *s2, char *sjoined)
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
	return (sjoined);
}

char	*gnl_strjoin(char *s1, char *s2)
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
	return (sjoined = ft_joined(s1, s2, sjoined));
}
