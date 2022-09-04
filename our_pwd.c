/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:50:45 by wgaspar           #+#    #+#             */
/*   Updated: 2022/08/31 16:50:46 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	my_pwd(char **args)
{
	char	*buf;

	if (args[0] && args[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	buf = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!buf)
		perror("Malloc in pwd: ");
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	free(buf);
	return (0);
}
