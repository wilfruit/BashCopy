#include "mini_shell.h"

char    **build_nested_command(t_shell *data, int cell_nb, char **args)
{
    char    **exp;
    char    **split;
    int     i;
    int     j;
    int     k;

    j = 0;
    i = 0;
    k = 0;
    exp = (char **)malloc(sizeof(char *) * (count_args(data, cell_nb) + search_in_charray(args, 34) + 1));
    if (!exp)
		return (NULL);
    while(args[i])
    {
        if (ft_strchr(args[i], ' ') && !ft_strchr(args[i], 34))
        {
            split = ft_split(args[i], ' ');
            j = 0;
            while (split[j])
            {
                exp[k] = ft_strdup(split[j]);
                k++;
                j++;
            }
        }
        i++;
    }
    exp[k] = NULL;
    ft_free_chr(split);
    ft_free_chr(args);
	return (exp);
}