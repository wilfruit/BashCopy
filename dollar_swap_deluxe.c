#include "mini_shell.h"

static int	input_has_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		return (i);
	else
		return (-1);
}

static int arrlen(char  **super)
{
    int i;

    i = 0;
    while(super[i])
        i++;
	i++;
    return (i);
}

char	*ft_hd_dollar_check(char *str, t_shell *pack)
{
	char	*ret;
	char	**stock;
	char	**translate;
	int			i;

	i = 0;
	if (input_has_dollar(str) == -1)
	{
		return (str);
	}
	ret = malloc(sizeof(char));
	ret = "\0";
	stock = ft_split(str, ' ');
	translate = (char **)malloc(sizeof(char *) * arrlen(stock));
	while (stock[i])
	{
		if (dollar_count(str) > 0 && dollar_swap(pack, ft_strdup(stock[i])))
			translate[i] = dollar_swap(pack, ft_strdup(stock[i]));
 		else if (dollar_count(str) > 0 && !dollar_swap(pack, ft_strdup(stock[i])))
			translate[i] = ft_strdup("");
		else
			translate[i] = ft_strdup(stock[i]);
		i++;
	}
	ft_free_chr(stock);
	translate[i] = NULL;
	ret = ft_strdup(translate[0]);
	i = 1;
	while (translate[i])
	{
		ret = ft_strjoin(ret, translate[i]);
		i++;
	}
	ft_free_chr(translate);
	free(str);
	return (ret);	
}