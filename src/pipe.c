/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:58:57 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 15:03:38 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_child(t_cmdlst *cmd)
{
	tcsetattr(0, TCSANOW, &g_term->init);
	if (cmd->pipes & PIPE_L)
	{
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[0]);
	}
	if (cmd->pipes & PIPE_R)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
}

int		do_pipe(t_cmdlst *cmd)
{
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
		manage_child(cmd);
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
