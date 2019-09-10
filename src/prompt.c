/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:45:44 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/09 17:24:59 by mguerrea         ###   ########.fr       */
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

int		wrong_quote(char *str)
{
	int i;
	int simple;
	int dbl;

	i = 0;
	simple = 0;
	dbl = 0;
	while (str[i])
	{
		i++;
		if (str[i] == '\'')
			simple++;
		if (str[i] == '"')
			dbl++;
	}
	return (simple % 2 + dbl % 2);
}
