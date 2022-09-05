#include "mini_shell.h"

char	*set_path(char **str)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", str[i], 5) != 0)
		i++;
	return (str[i] + 5);
}

int	help_size(int *i, char *line)
{
	while (line[*i] == ' ')
		*i += 1;
	if (line[*i] == '\0')
		return (0);
}

int	help_simple(int *i, char *line)
{
	*i += 1;
	while (line[*i] && line[*i] != '\'')
		*i += 1;
	return (0);
}

int	help_double(int *i, char *line)
{
	*i += 1;
	while (line[*i] && line[*i] != '\"')
		*i += 1;
	return (0);
}

/* int	size_cmd_tab(char *line)
{
	t_cmdtab	data;

	ft_init_cmdtab(&data);
	while (line[data.i])
	{
		if (line[data.i] == ' ')
		{
			help_size(&data.i, line);
			if (line[data.i] == '\0' && data.vu)
				return (data.size);
		}
		if (line[data.i] == '\0')
			return (0);
		if (line[data.i] == '\'')
			help_simple(&data.i, line);
		if (line[data.i] == '\"')
			help_double(&data.i, line);
		if (line[data.i] == '|')
			data.size++;
		if (line[data.i])
			ft_increment_cmdtab(&data);
	}
	return (data.size);
}
 */

 int	size_cmd_tab(char *line)
{
	int	i;
	int vu;
	int	size;

	i = 0;
	vu = 0;
	size = 1;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			help_size(&i, line);
			if (line[i] == '\0' && vu)
				return (size);
		}
		if (line[i] == '\0')
			return (0);
		if (line[i] == '\'')
			help_simple(&i, line);
		if (line[i] == '\"')
			help_double(&i, line);
		if (line[i] == '|')
			size++;
		if (line[i])
		{
			i++;
			vu++;
		}
	}
	return (size);
}
