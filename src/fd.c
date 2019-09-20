/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:41:47 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/20 17:55:17 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh_parser.h"

int		*save_fd(t_cmdlst *cmd)
{
	int *saved;

	if (!(saved = malloc(sizeof(int) * 4)))
		return (NULL);
	saved[0] = fcntl(cmd->redir[1].fd[0], F_DUPFD, 3);
	saved[1] = fcntl(cmd->redir[0].fd[0], F_DUPFD, 3);
	saved[2] = fcntl(cmd->redir[1].fd[1], F_DUPFD, 3);
	saved[3] = fcntl(cmd->redir[0].fd[1], F_DUPFD, 3);
	return (saved);
}

void	restore_fd(t_cmdlst *cmd, int *saved)
{
	if (dup2(saved[0], cmd->redir[1].fd[0]) == -1)
		close(cmd->redir[1].fd[0]);
	dup2(saved[1], cmd->redir[0].fd[0]);
	dup2(saved[2], cmd->redir[1].fd[1]);
	dup2(saved[3], cmd->redir[0].fd[1]);
	close(saved[0]);
	close(saved[1]);
	close(saved[2]);
	close(saved[3]);
	free(saved);
}

int		aggregate(t_cmdlst *cmd)
{
	int fildes;

	if (cmd->redir[1].file == NULL && cmd->redir[1].type == SPL)
	{
		if (!(isatty(fildes = cmd->redir[1].fd[1])) && !(cmd->redir[1].fd[1] == 1 && cmd->pipes == PIPE_R))
			return (error_fd(fildes));
		dup2(fildes, cmd->redir[1].fd[0]);
		if (cmd->redir[1].close == 1)
			close(cmd->redir[1].fd[0]);
	}
	if (cmd->redir[0].file == NULL && cmd->redir[0].type == SPL)
	{
		if (!(isatty(fildes = cmd->redir[0].fd[1])) && !(cmd->redir[0].fd[1] == 1 && cmd->pipes == PIPE_R))
			return (error_fd(fildes));
		dup2(fildes, cmd->redir[0].fd[0]);
		if (cmd->redir[0].close == 1)
			close(cmd->redir[0].fd[0]);
	}
	return (1);
}
