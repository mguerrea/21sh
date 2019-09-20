/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:07:24 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/20 17:57:54 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			format_tilde(char **word)
{
	char	*temp;
	char	*home;

	if (!(home = getenv("HOME")))
		home = getpwuid(getuid())->pw_dir;
	if (!(temp = ft_strjoin(home, (*word) + 1)))
		malloc_error();
	free(*word);
	*word = temp;
}

static size_t	count_args(t_token *words)
{
	size_t	len;

	len = 0;
	while (words)
	{
		++len;
		words = words->next;
	}
	return (len);
}

void			format_args(t_cmdlst *cmd, char **environ)
{
	size_t	i;
	size_t	len;
	t_token	*words;

	(void)**environ;
	words = cmd->argslst;
	len = count_args(cmd->argslst);
	i = 0;
	if (!(cmd->args = (char**)malloc(sizeof(char*) * (len + 1))))
		malloc_error();
	while (words)
	{
		if (words->word && words->word[0] == '~')
			format_tilde(&(words->word));
		format_var(&(words->word));
		cmd->args[i] = ft_trimquotes(words->word);
		++i;
		words = words->next;
	}
	cmd->args[i] = NULL;
}
