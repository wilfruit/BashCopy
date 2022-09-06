#include "../mini_shell.h"

void	help_help(int *i, int *j, int *k, t_pipe **prompt)
{
    (*prompt)[*i].scmd[*k].len_value += 1;
		*j += 1;
}