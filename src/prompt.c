/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:45:44 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 13:06:16 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(int *pos)
{
	char buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	ft_putstr(ft_strrchr(buf, '/') + 1);
	ft_putstr(" $> ");
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
	return wrong_quote_rec(str, 0);
	// int i;
	// int simple;
	// int dbl;

	// i = 0;
	// simple = 0;
	// dbl = 0;
	// while (str[i])
	// {
	// 	i++;
	// 	if (str[i] == '\'')
	// 		simple++;
	// 	if (str[i] == '"')
	// 		dbl++;
	// }
	// return (simple % 2 + dbl % 2);
}
