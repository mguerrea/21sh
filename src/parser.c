/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:09:03 by gmichaud          #+#    #+#             */
/*   Updated: 2019/04/13 17:33:19 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(t_cmdlst *cmd)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		cmd->redir[i].type = NONE;
		cmd->redir[i].file = NULL;
		++i;
	}
	cmd->redir[0].fd[0] = STDIN_FILENO;
	cmd->redir[0].fd[1] = STDIN_FILENO;
	cmd->redir[1].fd[0] = STDOUT_FILENO;
	cmd->redir[1].fd[1] = STDOUT_FILENO;
}

t_cmdlst	*cmd_name(t_token **tkn)
{
	t_cmdlst	*cmd;

	cmd = NULL;
	if ((*tkn)->type == WORD)
	{
		if (!(cmd = (t_cmdlst*)malloc(sizeof(t_cmdlst))))
			return (NULL);
		init_redir(cmd);
		cmd->pipes = 0;
		cmd->argslst = tkn_create((*tkn)->word);
		cmd->next = NULL;
		cmd->prev = NULL;
		*tkn = (*tkn)->next;
	}
	return (cmd);
}

int			filename(t_token **tkn, t_redir *redir)
{
	if ((*tkn)->type == WORD)
	{
		redir->file = (*tkn)->word;
		*tkn = (*tkn)->next;
		return (1);
	}
	return (0);
}

int			is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

int			get_fd(t_token **tkn, t_redir *redir)
{
	if ((*tkn)->type == WORD && is_number((*tkn)->word))
	{
		redir->fd[1] = ft_atoi((*tkn)->word);
		*tkn = (*tkn)->next;
		return (1);
	}
	return (0);
}

int		io_file(t_token **tkn, t_cmdlst *cmd)
{
	if ((*tkn)->type == GREAT)
	{
		cmd->redir[1].type = SPL;
		*tkn = (*tkn)->next;
		filename(tkn, &cmd->redir[1]);
		return (1);
	}
	else if ((*tkn)->type == DGREAT)
	{
		cmd->redir[1].type = DBL;
		*tkn = (*tkn)->next;
		filename(tkn, &cmd->redir[1]);
		return (1);
	}
	else if ((*tkn)->type == GREATAND)
	{
		cmd->redir[1].type = SPL;
		*tkn = (*tkn)->next;
		if (!get_fd(tkn, &cmd->redir[1]))
			filename(tkn, &cmd->redir[1]);
		return (1);
	}
	else if ((*tkn)->type == LESS)
	{
		cmd->redir[0].type = SPL;
		*tkn = (*tkn)->next;
		filename(tkn, &cmd->redir[0]);
		return (1);
	}
	else if ((*tkn)->type == LESSAND)
	{
		cmd->redir[1].type = SPL;
		*tkn = (*tkn)->next;
		if (!get_fd(tkn, &cmd->redir[0]))
			filename(tkn, &cmd->redir[0]);
		return (1);
	}
	return (0);
}

int		io_redirect(t_token **tkn, t_cmdlst *cmd)
{
	return (io_file(tkn, cmd));
}

void		cmd_suffix(t_token **tkn, t_cmdlst *cmd)
{
	if (*tkn)
	{
		if ((*tkn)->type == WORD)
		{
			tkn_lst_append(&cmd->argslst, tkn_create((*tkn)->word));
			*tkn = (*tkn)->next;
			cmd_suffix(tkn, cmd);
		}
		else if (io_redirect(tkn, cmd))
		{
			cmd_suffix(tkn, cmd);
		}
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
		if (*lst)
			(*lst)->prev = cmd;
		cmd->next = *lst;
		*lst = cmd;
	}
}

void cmd_lst_append(t_cmdlst **lst, t_cmdlst *cmd)
{
	t_cmdlst *tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = cmd;
	}
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
		cmd->prev = tmp;
	}
}

t_cmdlst	*cmd_lst_gotoend(t_cmdlst *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	pipe_sequence(t_token **tkn, t_cmdlst **cmdlst, t_pipemask pipe)
{
	t_cmdlst	*cmd;

	cmd = simple_cmd(tkn);
	if (!cmd)
		return;
	cmd->pipes |= pipe;	
	cmd_lst_append(cmdlst, cmd);
	if (*tkn && (*tkn)->type == PIPE)
	{
		cmd->pipes |= PIPE_R;
		*tkn = (*tkn)->next;
		pipe_sequence(tkn, cmdlst, PIPE_L);
	}
}

void		list(t_token **tkn, t_cmdlst **cmdlst)
{
	pipe_sequence(tkn, cmdlst, 0);
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
	list(&tknlst, &cmdlst);
	return (cmdlst);
}
