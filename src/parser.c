/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:09:03 by gmichaud          #+#    #+#             */
/*   Updated: 2019/10/04 16:23:12 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		cmd_suffix(t_token **tkn, t_cmdlst *cmd)
{
	if (*tkn)
	{
		if ((*tkn)->type == WORD)
		{
			tkn_lst_append(&cmd->argslst, tkn_create((*tkn)->word));
			*tkn = (*tkn)->next;
			return (cmd_suffix(tkn, cmd));
		}
		else if (((*tkn)->type == PIPE || (*tkn)->type == SEMI))
		{
			return (1);
		}
		else if (io_redirect(tkn, cmd))
		{
			return (cmd_suffix(tkn, cmd));
		}
		else
		{
			return (0);
		}
	}
	return (1);
}

static t_cmdlst	*simple_cmd(t_token **tkn)
{
	t_cmdlst	*cmd;

	cmd = NULL;
	if (*tkn && (cmd = cmd_create()))
	{
		while (*tkn)
		{
			if ((*tkn)->type == PIPE || (*tkn)->type == SEMI)
				return (cmd);
			if (!cmd_suffix(tkn, cmd))
			{
				free_cmd(&cmd);
				return (NULL);
			}
		}
	}
	return (cmd);
}

static int		pipe_sequence(t_token **tkn, t_cmdlst **cmdlst, t_pipemask pipe)
{
	t_cmdlst	*cmd;

	cmd = simple_cmd(tkn);
	if (!cmd)
		return (0);
	cmd->pipes |= pipe;
	cmd_lst_append(cmdlst, cmd);
	if (*tkn && (*tkn)->type == PIPE)
	{
		cmd->pipes |= PIPE_R;
		*tkn = (*tkn)->next;
		if (*tkn && ((*tkn)->type == SEMI || (*tkn)->type == PIPE))
			return (0);
		return (pipe_sequence(tkn, cmdlst, PIPE_L));
	}
	return (1);
}

static int		list(t_token **tkn, t_cmdlst **cmdlst)
{
	if (!pipe_sequence(tkn, cmdlst, 0))
		return (0);
	if (*tkn && (*tkn)->type == SEMI)
	{
		*tkn = (*tkn)->next;
		if (*tkn && ((*tkn)->type == SEMI || (*tkn)->type == PIPE))
			return (0);
		list(tkn, cmdlst);
	}
	return (1);
}

t_cmdlst		*parse(t_token *tknlst)
{
	t_cmdlst	*cmdlst;

	cmdlst = NULL;
	if (tknlst && !list(&tknlst, &cmdlst))
	{
		if (tknlst)
		{
			ft_putstr_fd("parse error near '", 2);
			ft_putstr_fd(tknlst->word, 2);
			ft_putstr_fd("'\n", 2);
		}
		else
		{
			ft_putstr_fd("parse error near '\\n'\n", 2);
		}
		free_cmdlst(&cmdlst);
	}
	return (cmdlst);
}
