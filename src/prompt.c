/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:45:44 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/20 14:47:53 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(int *pos)
{
	char buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	ft_putstr_fd(ft_strrchr(buf, '/') + 1, 2);
	ft_putstr_fd(" $> ", 2);
	*pos = 0;
}

int		wrong_quote_rec(char *str, char current_quote)
{
	char quote;

	quote = 0;
	if (!*str)
		return (current_quote != 0);
	if (*str == current_quote)
		return (wrong_quote_rec(++str, 0));
	if (!current_quote && (*str == '"' || *str == '\''))
	{
		quote = *str;
		return (wrong_quote_rec(++str, quote));
	}
	return (wrong_quote_rec(++str, current_quote));
}

int		wrong_quote(char *str)
{
	return (wrong_quote_rec(str, 0));
}
