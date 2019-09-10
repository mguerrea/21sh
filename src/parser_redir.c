/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:13:39 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/10 16:59:03 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	filename(t_token **tkn, t_redir *redir)
{
	if (*tkn && (*tkn)->type == WORD)
	{
		redir->file = ft_strdup((*tkn)->word);
		*tkn = (*tkn)->next;
		return (1);
	}
	return (0);
}

static int	get_fd(t_token **tkn, t_redir *redir)
{
	if (*tkn && (*tkn)->type == WORD && is_number((*tkn)->word))
	{
		redir->fd[1] = ft_atoi((*tkn)->word);
		*tkn = (*tkn)->next;
		return (1);
	}
	return (0);
}

static int	io_file_in(t_token **tkn, t_cmdlst *cmd, t_token *io_number)
{
	t_tkn_type	redir_type;

	cmd->redir[0].type = (*tkn)->type == DLESS ? DBL : SPL;
	redir_type = (*tkn)->type;
	if (io_number)
		cmd->redir[0].fd[0] = ft_atoi(io_number->word);
	*tkn = (*tkn)->next;
	if (redir_type == DLESS)
		return (heredoc(tkn, &cmd->redir[0]));
	else if (redir_type == LESSAND)
	{
		if (!get_fd(tkn, &cmd->redir[0]))
			return (filename(tkn, &cmd->redir[0]));
		return (1);
	}
	return (filename(tkn, &cmd->redir[0]));
}

static int	io_file_out(t_token **tkn, t_cmdlst *cmd, t_token *io_number)
{
	t_tkn_type	redir_type;

	cmd->redir[1].type = (*tkn)->type == DGREAT ? DBL : SPL;
	redir_type = (*tkn)->type;
	if (io_number)
		cmd->redir[1].fd[0] = ft_atoi(io_number->word);
	*tkn = (*tkn)->next;
	if (redir_type == GREATAND)
	{
		if (!get_fd(tkn, &cmd->redir[1]))
			return (filename(tkn, &cmd->redir[1]));
		return (1);
	}
	else
	{
		return (filename(tkn, &cmd->redir[1]));
	}
	return (0);
}

int			io_redirect(t_token **tkn, t_cmdlst *cmd)
{
	t_token	*io_number;

	io_number = NULL;
	if ((*tkn)->type == IO_NUMBER)
	{
		io_number = *tkn;
		*tkn = (*tkn)->next;
	}
	if ((*tkn)->type == GREAT || (*tkn)->type == DGREAT
		|| (*tkn)->type == GREATAND)
		return (io_file_out(tkn, cmd, io_number));
	else if ((*tkn)->type == LESS || (*tkn)->type == DLESS
		|| (*tkn)->type == LESSAND)
		return (io_file_in(tkn, cmd, io_number));
	else
		return (0);
}
