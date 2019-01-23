/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 12:45:41 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/23 16:48:03 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int do_pipe(t_cmdlst *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		ft_putendl_fd("fork error", 2);
	else if (pid == 0)
	{
		if (cmd->pipes & PIPE_L)
		{
			dup2(cmd->prev->fd[0], STDIN_FILENO);
			close(cmd->prev->fd[1]);
		}
		if (cmd->pipes & PIPE_R)
		{
			dup2(cmd->fd[1], STDOUT_FILENO);
			close(cmd->fd[0]);
		}
	}
	else
	{
		wait(NULL);
		close(cmd->fd[1]);
		if (cmd->prev)
			close(cmd->prev->fd[0]);
	}
	return (pid);
}