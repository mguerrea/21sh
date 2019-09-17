/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:41:11 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/17 19:54:30 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_content(char *end_word, char *content)
{
	char	*line;
	char	*new_content;
	size_t	len;

	new_content = NULL;
	line = get_heredoc();
	len = ft_strlen(line);
	if ((!ft_strncmp(line, end_word, ft_strlen(end_word))
		&& ft_strlen(end_word) + 1 == len)
		|| line[len - 1] == 4)
	{
		free(line);
		return (content);
	}
	if (!content)
		new_content = line;
	else
	{
		if (!(new_content = ft_strjoin(content, line)))
			malloc_error();
		free(content);
		free(line);
	}
	return (get_heredoc_content(end_word, new_content));
}

int			heredoc(t_token **tkn, t_redir *redir)
{
	// char *content;
	// char *final;

	// content = NULL;
	// final = NULL;
	if (*tkn && (*tkn)->type == WORD)
	{
		redir->file = get_heredoc_content((*tkn)->word, redir->file);
		// if (!redir->file)
		// 	redir->file = content;
		// else
		// {
		// 	if (!(final = ft_strjoin(redir->file, content)))
		// 		malloc_error();
		// 	ft_strdel(&(redir->file));
		// 	ft_strdel(&content);
		// 	redir->file = final;
		// }
		*tkn = (*tkn)->next;
		return (1);
	}
	return (0);
}
