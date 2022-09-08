#include "../mini_shell.h"

int	infile_not_allowed_m(t_exec_multi *pack, int cell_nb, t_shell *data, int i)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(data->token[cell_nb].scmd[i + 1].value, 2);
	ft_putendl_fd(" Permission denied", 2);
	data->error_ret = 1;
	return (1);
}

int	infile_not_real_m(t_exec_multi *pack, int cell_nb, t_shell *data, int i)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(data->token[cell_nb].scmd[i + 1].value, 2);
	ft_putendl_fd(" No such file or directory", 2);
	data->error_ret = 1;
	return (1);
}

int	outfile_not_allowed_m(t_exec_multi *pack, int cell_nb, t_shell *data, int i)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(data->token[cell_nb].scmd[i + 1].value, 2);
	ft_putendl_fd(" Permission denied", 2);
	data->error_ret = 1;
	return (1);
}

void	init_sig(void)
{
	int	i;

	i = -150000;
	while (i < 3000000)
		i++;
	return ;
}