/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:07:24 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 12:50:20 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_trimquotes(char *s)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	j;
// 	size_t	k;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	while (s[i] == '"')
// 		i++;
// 	j = ft_strlen((char *)s) - 1;
// 	while ((s[j] == '"') && j > i)
// 		j--;
// 	if (!(str = ft_strnew(j - i + 1)))
// 		return (NULL);
// 	k = -1;
// 	while (++k < j - i + 1)
// 		str[k] = s[i + k];
// 	return (str);
// }

size_t	get_new_len(char *s, char current_quote)
{
	char quote;

	quote = 0;
	if (!(*s))
		return (0);
	if (*s == current_quote)
		return (get_new_len(++s, 0));
	if (!current_quote && (*s == '"' || *s == '\''))
	{
		quote = *s;
		return (get_new_len(++s, quote));
	}
	return (get_new_len(++s, current_quote) + 1);
}

void	get_copy(char *src, char *dest, char current_quote)
{
	char quote;

	quote = 0;
	// printf("%c; %c\n", *src, current_quote);
	if (!(*src))
		return ;
	else if (*src == current_quote)
		get_copy(++src, dest, 0);
	else if (!current_quote && (*src == '"' || *src == '\''))
	{
		quote = *src;
		get_copy(++src, dest, quote);
	}
	else
	{
		*dest = *src;
		get_copy(++src, ++dest, current_quote);
	}
}

char	*ft_trimquotes(char *s)
{
	size_t	new_len;
	char *str;

	if (!s)
		return (NULL);
	new_len = get_new_len(s, 0);
	str = NULL;
	if (!(str = ft_strnew(new_len)))
		return (NULL);
	get_copy(s, str, 0);
	return (str);
}

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

// void	format_args(char ***args, char **environ)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while ((*args)[i])
// 	{
// 		tmp = ft_strtrim((*args)[i]);
// 		ft_strdel(&((*args)[i]));
// 		if (tmp[0] == '~')
// 			format_tilde(&tmp, environ);
// 		(*args)[i] = ft_trimquotes(tmp);
// 		ft_strdel(&tmp);
// 		if ((*args)[i][0] == '$')
// 			format_var(&((*args)[i]), environ);
// 		i++;
// 	}
// }

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
