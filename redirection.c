#include "mini_shell.h"

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	which_redirection(char c, int len_token)
{
	if (len_token == 1)
	{
		if (c == '>')
			return (TOKEN_OUTPUT_REDIRECTION);
		else
			return (TOKEN_INTPUT_REDIRECTION);
	}
	else
	{
		if (c == '>')
			return (TOKEN_OUTPUT_APPEND_EDIRECTION);
		else
			return (TOKEN_INTPUT_HEREDOC_REDIRECTION);
	}
	return (0);
}

char	*check_line(char **line)
{
	if (*line == NULL)
	{
		write(1, "exit\n", 5);
		free(*line);
		return (NULL);
	}
	return (*line);
}

void	*determine_type(t_pipe *prompt)
{
	int	i;

	i = -1;
	while (++i < prompt->nb_token)
	{
		prompt->scmd[i].type = 0;
		if (i == 0 && !is_redirection(prompt->scmd[i].value[i]))
			prompt->scmd[i].type = TOKEN_CMD;
		else if (is_redirection(prompt->scmd[i].value[0]))
			prompt->scmd[i].type = which_redirection(prompt->scmd[i].value[0] \
			, prompt->scmd[i].len_value);
		else if (i > 0 && (prompt->scmd[i - 1].type == 0 || \
		prompt->scmd[i - 1].type == 1))
			prompt->scmd[i].type = TOKEN_ARG;
		else if (i > 0 && is_redirection(prompt->scmd[i - 1].value[0]))
		{
			prompt->scmd[i].type = TOKEN_FILE;
			if (which_redirection(prompt->scmd[i - 1].value[0], \
			prompt->scmd[i - 1].len_value) == TOKEN_INTPUT_HEREDOC_REDIRECTION)
				prompt->scmd[i].type = TOKEN_LIMITER;
		}	
		else if (i > 0 && ((prompt->scmd[i - 1].type == TOKEN_FILE) || \
		(prompt->scmd[i - 1].type == TOKEN_LIMITER)))
			prompt->scmd[i].type = TOKEN_CMD;
		else
			prompt->scmd[i].type = TOKEN_ERROR;
	}	
}
