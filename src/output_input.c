/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 12:45:41 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 13:06:34 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int do_pipe(t_cmdlst *cmd)
{
	//	pid_t pid;
	int mypipe[2];

	if (cmd->pipes & PIPE_R)
	{
		if (pipe(mypipe) < 0)
			return (-1);
		cmd->fd[1] = mypipe[1];
		cmd->next->fd[0] = mypipe[0];
	}
	if ((g_pid = fork()) == -1)
		ft_putendl_fd("fork error", 2);
	else if (g_pid == 0)
	{
		tcsetattr(0, TCSANOW, &g_term->init);
		if (cmd->pipes & PIPE_L) // piped with last process
		{
			dup2(cmd->fd[0], STDIN_FILENO);
			close(cmd->fd[0]);
		}
		if (cmd->pipes & PIPE_R) // piped with next process
		{
			dup2(cmd->fd[1], STDOUT_FILENO);
			close(cmd->fd[1]);
		}
	}
	else
	{
		catch_signals(0, NULL, NULL);
		wait(NULL);
		if (cmd->pipes & PIPE_L)
			close(cmd->fd[0]);
		if (cmd->pipes & PIPE_R)
			close(cmd->fd[1]);
		tcsetattr(0, TCSANOW, &g_term->cur);
	}
	return (g_pid);
}

void create_files(t_cmdlst *cmd)
{
	int fildes;

	if (cmd->pipes & PIPE_R)
	{
		cmd = cmd->next;
	while (cmd && (cmd->pipes & PIPE_L))
	{
		if (cmd->redir[1].type && cmd->redir[1].file)
		{
			if ((fildes = open(cmd->redir[1].file, O_CREAT | O_RDWR | O_TRUNC, 0666)) != -1)
				close(fildes);
		}
		cmd = cmd->next;
	}
	}
}

int redir_out(t_cmdlst *cmd)
{
	int fildes;

	fildes = 0;
	if ((cmd->redir[1].file == NULL || cmd->redir[1].file[0] == '-') && cmd->redir[1].type == SPL)
	{
		if (!(isatty(fildes = cmd->redir[1].fd[1])) && !(cmd->redir[1].fd[1] == 1 && cmd->pipes == PIPE_R))
			return (error_fd(fildes));
	}
	else if (cmd->redir[1].file[0] != '-' && cmd->redir[1].type == SPL)
	{
		if ((fildes = open(cmd->redir[1].file, O_CREAT | O_RDWR | O_TRUNC, 0666)) == -1)
		{
			error_file(NULL, cmd->redir[1].file);
			return (-1);
		}
	}
	else if (cmd->redir[1].file[0] != '-' && cmd->redir[1].type == DBL)
	{
		if ((fildes = open(cmd->redir[1].file, O_CREAT | O_RDWR | O_APPEND, 0666)) == -1)
		{
			error_file(NULL, cmd->redir[1].file);
			return (-1);
		}
	}
	dup2(fildes, cmd->redir[1].fd[0]);
	close(fildes);
	if (cmd->redir[1].file && cmd->redir[1].file[0] == '-')
		close(cmd->redir[1].fd[0]);
	return (1);
}

int here_doc(t_cmdlst *cmd)
{
	int fildes[2];

	if (pipe(fildes) == -1)
		return (-1);
	write(fildes[1], cmd->redir[0].file, ft_strlen(cmd->redir[0].file));
	close(fildes[1]);
	return (fildes[0]);
}

int redir_in(t_cmdlst *cmd)
{
	int fildes;

	fildes = 0;
	if ((cmd->redir[0].file == NULL || cmd->redir[0].file[0] == '-') && cmd->redir[0].type == SPL)
	{
		if (!(isatty(fildes = cmd->redir[0].fd[1])))
			return (error_fd(fildes));
	}
	else if (cmd->redir[0].file && cmd->redir[0].type == SPL)
	{
		if ((fildes = open(cmd->redir[0].file, O_RDONLY)) == -1)
		{
			error_file(NULL, cmd->redir[0].file);
			return (-1);
		}
	}
	else if (cmd->redir[0].type == DBL)
		fildes = here_doc(cmd);
	dup2(fildes, cmd->redir[0].fd[0]);
	close(fildes);
	if (cmd->redir[0].file && cmd->redir[0].file[0] == '-')
		close(cmd->redir[0].fd[0]);
	return (1);
}

int redirection(t_cmdlst *cmd)
{
	if (cmd->redir[1].type != NONE && redir_out(cmd) == -1)
		return (-1);
	if (cmd->redir[0].type != NONE && redir_in(cmd) == -1)
		return (-1);
	return (1);
}
