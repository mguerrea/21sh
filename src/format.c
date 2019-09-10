/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:07:24 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 16:00:11 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		format_var(char **var, char **environ)
{
	char **value;

	if (!(value = ft_getenv(environ, *(var) + 1)))
		return (-1);
	ft_strdel(var);
	if (!(*var = ft_strjointab(value, ':')))
		return (-1);
	free_tab(value);
	return (1);
}

int		format_tilde(char **args, char **environ)
{
	char **var;
	char *temp;
	char *home;

	if (!(var = ft_getenv(environ, "HOME")))
		home = getpwuid(getuid())->pw_dir;
	else
		home = var[0];
	temp = ft_strjoin(home, (*args) + 1);
	free(*args);
	*args = temp;
	free_tab(var);
	return (1);
}

size_t	count_args(t_token *words)
{
	size_t len;

	len = 0;
	while (words)
	{
		++len;
		words = words->next;
	}
	return (len);
}

void	format_args(t_cmdlst *cmd, char **environ)
{
	size_t	i;
	size_t	len;
	t_token	*words;

	(void)**environ;
	words = cmd->argslst;
	len = count_args(cmd->argslst);
	i = 0;
	cmd->args = (char**)malloc(sizeof(char*) * (len + 1));
	while (words)
	{
		cmd->args[i] = ft_trimquotes(words->word);
		++i;
		words = words->next;
	}
	cmd->args[i] = NULL;
}
