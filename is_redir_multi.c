#include "mini_shell.h"

int count_redir_out_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (i < data->token[cell_nb].nb_token - 1)
    {
        if (data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_REDIRECTION || \
        data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_APPEND_EDIRECTION)
            count++;
        i++;
    }
    return (count);
}

int count_redir_in_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (i < data->token[cell_nb].nb_token - 1)
    {
        if (data->token[cell_nb].scmd[i].type == TOKEN_INTPUT_REDIRECTION)
            count++;
        i++;
    }
    return (count);
}

int count_redir_heredoc_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (i < data->token[cell_nb].nb_token - 1)
    {
        if (data->token[cell_nb].scmd[i].type == TOKEN_INTPUT_HEREDOC_REDIRECTION)
            count++;
        i++;
    }
    return (count);
}

void treat_redir_out_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while ((data->token[cell_nb].scmd[i].type != 2 && data->token[cell_nb].scmd[i].type != 3) \
    && i < data->token[cell_nb].nb_token)
        i++;
    while (j < pack->nb_redirout)
    {
        if (data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_REDIRECTION)
            pack->redirout = open(data->token[cell_nb].scmd[i + 1].value, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_APPEND_EDIRECTION)
            pack->redirout = open(data->token[cell_nb].scmd[i + 1].value, O_CREAT | O_RDWR | O_APPEND, 0644);
        i += 2;
        j++;
    }
}

void treat_redir_in_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (data->token[cell_nb].scmd[i].type != 4 \
    && i < data->token[cell_nb].nb_token)
        i++;
    while (j < pack->nb_redirin)
    {
        if (data->token[cell_nb].scmd[i].type == TOKEN_INTPUT_REDIRECTION)
            pack->redirin = open(data->token[cell_nb].scmd[i + 1].value, O_RDONLY);
        i += 2;
        j++;
    }
}