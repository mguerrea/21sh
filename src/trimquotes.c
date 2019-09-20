/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:59:52 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/20 18:01:56 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_new_len(char *s, char current_quote)
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

static void		get_copy(char *src, char *dest, char current_quote)
{
	char quote;

	quote = 0;
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

char			*ft_trimquotes(char *s)
{
	size_t	new_len;
	char	*str;

	if (!s)
		return (NULL);
	new_len = get_new_len(s, 0);
	str = NULL;
	if (!(str = ft_strnew(new_len)))
		return (NULL);
	get_copy(s, str, 0);
	return (str);
}
