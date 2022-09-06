#include "../mini_shell.h"

void    ft_incr(t_cmdtab *d)
{
    d->i++;
    d->vu++;
}

void    legi_incr(int *k, int *v)
{
    *k += 1;
    *v = 0;
}
void    legi_incr2(int *v, int *j)
{
    *v += 1;
    *j += 1;
}
void	check_dolls(t_pipe **prompt, t_manage_pipe *data)
{
    if ((*prompt)[data->i].cmd[data->j] == '$')
	    (*prompt)[data->i].scmd[data->k].is_dollar = DOLLAR_MACRO;
}
void    help_built_struct(int *len_cmd, int *first)
{
    *len_cmd += 1;
	*first = 1;
}