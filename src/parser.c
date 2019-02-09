/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:09:03 by gmichaud          #+#    #+#             */
/*   Updated: 2019/02/09 18:53:24 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlst	*cmd_name(t_token **tkn)
{
	t_cmdlst	*cmd;

	cmd = NULL;
	if ((*tkn)->type == WORD)
	{
		if (!(cmd = (t_cmdlst*)malloc(sizeof(t_cmdlst))))
			return (NULL);
		cmd->argslst = tkn_create((*tkn)->word);
		cmd->next = NULL;
		cmd->prev = NULL;
		*tkn = (*tkn)->next;
	}
	return (cmd);
}

void		cmd_suffix(t_token **tkn, t_cmdlst *cmd)
{
	while (*tkn && (*tkn)->type == WORD)
	{
		tkn_lst_push(&cmd->argslst, tkn_create((*tkn)->word));
		*tkn = (*tkn)->next;
	}
}

t_cmdlst	*simple_cmd(t_token **tkn)
{
	t_cmdlst	*cmd;

	cmd = NULL;
	if (*tkn && (cmd = cmd_name(tkn)))
	{
		while (*tkn)
		{
			if ((*tkn)->type == PIPE || (*tkn)->type == SEMI)
				return (cmd);
			cmd_suffix(tkn, cmd);
		}
	}
	return (cmd);
}

void	cmd_lst_push(t_cmdlst **lst, t_cmdlst *cmd)
{
	if (lst && cmd)
	{
		cmd->next = *lst;
		*lst = cmd;
	}
}

void	pipe_sequence(t_token **tkn, t_cmdlst **cmdlst)
{
	t_cmdlst	*cmd;

	cmd = simple_cmd(tkn);
	cmd_lst_push(cmdlst, cmd);
	if (*tkn && (*tkn)->type == PIPE)
	{
		if (!*cmdlst)
			return ;
		(*cmdlst)->pipes |= PIPE_R;
		*tkn = (*tkn)->next;
		pipe_sequence(tkn, cmdlst);
		(*cmdlst)->pipes |= PIPE_L;
	}
}

void		list(t_token **tkn, t_cmdlst **cmdlst)
{
	pipe_sequence(tkn, cmdlst);
	// cmd_lst_push(cmdlst, cmd);
	if (*tkn && (*tkn)->type == SEMI)
	{
		*tkn = (*tkn)->next;
		list(tkn, cmdlst);
	}
}

t_cmdlst	*parse(t_token *tknlst)
{
	t_cmdlst	*cmdlst;

	cmdlst = NULL;
	if (!tknlst)
		return (NULL);
	// if (tknlst->type == PIPE || tknlst->type == SEMI)
	// {
	// 	ft_putstr("Unexpected token `");
	// 	ft_putstr(tknlst->word);
	// 	ft_putendl("'");
	// 	return (NULL);
	// }
	// while (tknlst)
	// {
	// 	if (tknlst->type == PIPE)
	// 		tknlst = tknlst->next;
	// 	if (tknlst->type == SEMI)
	// 	cmd_lst_push(&cmdlst, simple_cmd(&tknlst));
	// }
	list(&tknlst, &cmdlst);
	return (cmdlst);
}
