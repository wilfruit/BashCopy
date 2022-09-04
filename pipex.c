#include "mini_shell.h"

static void	child_first(t_shell *data, t_exec_multi *pack)
{
	pipe(pack->pipe_fd[0]);
	pack->c_pid[0] = fork();
	if (pack->c_pid[0] < 0)
		perror("Fork :");
	if (pack->c_pid[0] == 0)
	{
		mini_parse_multi(data, pack, 0);
		close(pack->pipe_fd[0][0]);
		if (get_last_redirin_m(data, pack, 0) != 5)
		{
			dup2(pack->pipe_fd[0][1], STDOUT_FILENO);
			close(pack->pipe_fd[0][1]);
		}
		if (pack->nb_redirin || pack->nb_redirout || pack->is_here_doc)
			redir_dup_multi(data, pack, 0);
		else
			ft_execve_multi(data, charize_env(data->our_env), pack);
	}	
	else
	{
		if (get_last_redirin_m(data, pack, 0) == TOKEN_INTPUT_HEREDOC_REDIRECTION)
			waitpid(pack->c_pid[0], NULL, 0);
		close(pack->pipe_fd[0][1]);
	}
}

static void	mid_process(t_shell *data, t_exec_multi *pack, int n)
{
	pipe(pack->pipe_fd[n]);
	pack->c_pid[n] = fork();
	if (pack->c_pid[n] < 0)
		perror("Fork :");
	if (pack->c_pid[n] == 0)
	{
		mini_parse_multi(data, pack, n);
		close(pack->pipe_fd[n][0]);
		if (!pack->nb_redirin && !pack->is_here_doc)
		{
			dup2(pack->pipe_fd[n - 1][0], STDIN_FILENO);
			close(pack->pipe_fd[n - 1][0]);
		}
		if (get_last_redirin_m(data, pack, n) != 5)
		{
			dup2(pack->pipe_fd[n][1], STDOUT_FILENO);
			close(pack->pipe_fd[n][1]);
		}
		if (pack->nb_redirin || pack->nb_redirout || pack->is_here_doc)
			redir_dup_multi(data, pack, n);
		else
		ft_execve_multi(data, charize_env(data->our_env), pack);
	}
	else
	{
		close(pack->pipe_fd[n - 1][0]);
		close(pack->pipe_fd[n][1]);
		if (get_last_redirin_m(data, pack, n) == TOKEN_INTPUT_HEREDOC_REDIRECTION)
			waitpid(pack->c_pid[n], NULL, 0);
	}
}

static void	last_child(t_shell *data, t_exec_multi *pack, int n)
{
	pack->c_pid[n] = fork();
	if (pack->c_pid[n] < 0)
		perror("Fork :");
	if (pack->c_pid[n] == 0)
	{
		mini_parse_multi(data, pack, n);
		if (!pack->nb_redirin && !pack->is_here_doc)
		{
 			dup2(pack->pipe_fd[n - 1][0], STDIN_FILENO);
			close(pack->pipe_fd[n - 1][0]);
		}
		if (pack->nb_redirin || pack->nb_redirout || pack->is_here_doc)
			redir_dup_multi(data, pack, n);
		else
		ft_execve_multi(data, charize_env(data->our_env), pack);
	}
	else
	{
		close(pack->pipe_fd[n - 1][0]);
		if (get_last_redirin_m(data, pack, n) == TOKEN_INTPUT_HEREDOC_REDIRECTION)
			waitpid(pack->c_pid[n], NULL, 0);
	}
}

static void	init_multi_exe(t_shell *data, t_exec_multi *exec_pack)
{
	if (data->our_env->next == NULL)
	{
		exec_pack->allpaths = (char **)malloc(sizeof(char *));
		exec_pack->allpaths[0] = NULL;
	}
	else
		exec_pack->allpaths = get_allpaths(data);
    malloc_childs(data, exec_pack);
    malloc_pipes(data, exec_pack);
	exec_pack->cmdargs = ft_calloc(PATH_MAX, sizeof(char *));
}

void	pipex(t_shell *data)
{
	int		i;
	t_exec_multi   exec_pack;

	i = 1;
    init_multi_exe(data, &exec_pack);
	child_first(data, &exec_pack);
	while (i < data->nb_cell - 1)
	{
		mid_process(data, &exec_pack, i);
		i++;
	}
	last_child(data, &exec_pack, i);
	wait_all(data, &exec_pack);
}