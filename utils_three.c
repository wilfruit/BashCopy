#include "mini_shell.h"

int	is_valid_identifier_exp(char *cmd)
{
	int	al_or_undersc;
	int	i;

	al_or_undersc = 0;
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (ft_isalpha(cmd[i]) || ft_strncmp(&cmd[i], "_", 1) == 0)
			al_or_undersc++;
		if (!ft_isalnum(cmd[i]) && ft_strncmp(&cmd[i], "_", 1) != 0)
			return (-1);
		i++;
	}
	if (al_or_undersc > 0)
		return (0);
	else
		return (-1);
}

void	*cpt_pipe(int *r, int *cmd, t_manage_pipe *mpipe, char *line)
{
		(*mpipe).size_cmd[*cmd] = (*mpipe).size;
		mpipe->size = 0;
		*cmd += 1;
		*r += 1;
}

int	len_redir(int *r, t_manage_pipe *mpipe, char *line)
{
	mpipe->size += 1;
	*r += 1;
	if (is_redirection(line[*r]) == 1)
	{
		if (line[*r - 1] != line[*r] || line[*r + 1] == line[*r])
			return (write(1, "syntax error near unexpected token\n", 35), 1);
		mpipe->size += 1;
		*r += 1;
	}	
		return (0);
}

void	*len_d_quote(int *r, t_manage_pipe *mpipe, char *line)
{
	if (line[*r] == '\"')
    {
        *r += 1;
	    mpipe->size += 1;
	    while (line[*r] && line[*r] != '\"')
	    {
		    mpipe->size += 1;
	    	*r += 1;
	    }
	    if (line[*r] != '\"')
	    	return (write(1, "invalid syntax\n", 15), NULL);
	    mpipe->size += 1;
	    *r += 1;
    }
    else
    {
        *r += 1;
	    mpipe->size += 1;
	    while (line[*r] && line[*r] != '\'')
	    {
		    mpipe->size += 1;
	    	*r += 1;
	    }
	    if (line[*r] != '\'')
	    	return (write(1, "invalid syntax\n", 15), NULL);
	    mpipe->size += 1;
	    *r += 1;
    }
}
