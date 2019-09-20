/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:09:44 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/20 16:35:00 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_redir(t_cmdlst *cmd)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		cmd->redir[i].type = NONE;
		cmd->redir[i].file = NULL;
		cmd->redir[i].close = 0;
		++i;
	}
	cmd->redir[0].fd[0] = STDIN_FILENO;
	cmd->redir[0].fd[1] = STDIN_FILENO;
	cmd->redir[1].fd[0] = STDOUT_FILENO;
	cmd->redir[1].fd[1] = STDOUT_FILENO;
}

t_cmdlst	*cmd_create(void)
{
	t_cmdlst	*cmd;

	cmd = NULL;
	if (!(cmd = (t_cmdlst*)malloc(sizeof(t_cmdlst))))
		return (NULL);
	init_redir(cmd);
	cmd->pipes = 0;
	cmd->exec = 0;
	cmd->args = NULL;
	cmd->argslst = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void		free_cmd(t_cmdlst **cmd)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if ((*cmd)->redir[i].file)
			free((*cmd)->redir[i].file);
		++i;
	}
	if ((*cmd)->args)
		free_tab((*cmd)->args);
	if ((*cmd)->argslst)
		tkn_lst_del(&((*cmd)->argslst));
	free(*cmd);
	cmd = NULL;
}

void		free_cmdlst(t_cmdlst **lst)
{
	t_cmdlst	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			free_cmd(&tmp);
		}
		*lst = NULL;
	}
}
