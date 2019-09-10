/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:41:11 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/10 15:44:56 by gmichaud         ###   ########.fr       */
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
		return (content);
	}
	if (!content)
	{
		new_content = line;
	}
	else
	{
		new_content = ft_strjoin(content, line);
		free(content);
		free(line);
	}
	return (get_heredoc_content(end_word, new_content));
}

int			heredoc(t_token **tkn, t_redir *redir)
{
	if (*tkn && (*tkn)->type == WORD)
	{
		redir->file = get_heredoc_content((*tkn)->word, NULL);
		*tkn = (*tkn)->next;
		return (1);
	}
	return (0);
}