/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:50:08 by mguerrea          #+#    #+#             */
/*   Updated: 2019/08/20 17:08:24 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_insert(char *line, char c, int pos)
{
	int i;

	i = ft_strlen(line);
	while (i > pos)
	{
		line[i] = line[i - 1];
		i--;
	}
	line[pos] = c;
}

void ft_delete(t_line *line)
{
	int len;
	int pos;

	pos = line->pos;
	len = ft_strlen(line->str);
	while (pos < len)
	{
		line->str[pos] = line->str[pos + 1];
		pos++;
	}
}