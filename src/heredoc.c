/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:41:11 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/20 18:34:28 by gmichaud         ###   ########.fr       */
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
	char	*unquoted;
	
	unquoted = NULL;
	if (*tkn && (*tkn)->type == WORD)
	{
		unquoted = ft_trimquotes((*tkn)->word);
		redir->file = get_heredoc_content(unquoted, redir->file);
		free(unquoted);
		*tkn = (*tkn)->next;
		return (1);
	}
	return (0);
}
