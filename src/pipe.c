/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:58:57 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/14 14:28:43 by mguerrea         ###   ########.fr       */
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
		close(cmd->next->fd[0]);
	}

}

int		do_pipe(t_cmdlst *cmd, char ***env)
{
	int mypipe[2];

	if (cmd->pipes & PIPE_R)
	{
		if (pipe(mypipe) < 0)
			return (-1);
		cmd->fd[1] = mypipe[1];
		cmd->next->fd[0] = mypipe[0];
	}
	int i = 0;
	while (g_pid[i] != -2)
		i++;
	g_pid[i + 1] = -2;
	if ((g_pid[i] = fork()) == -1)
		ft_putendl_fd("fork error", 2);
	else if (g_pid[i] == 0)
		manage_child(cmd);
	else
	{
		catch_signals(0, NULL, NULL);
		if (cmd->pipes & PIPE_L)
			close(cmd->fd[0]);
		if (cmd->pipes & PIPE_R)
		{
			close(cmd->fd[1]);
			iter_cmd(cmd->next, 1, env);
		}
		waitpid(g_pid[i], NULL, WUNTRACED);
		g_pid[i] = -2;
		if (i == 0)
			tcsetattr(0, TCSANOW, &g_term->cur);
	}
	return (g_pid[i]);
}
