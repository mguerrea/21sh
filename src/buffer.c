/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:50:08 by mguerrea          #+#    #+#             */
/*   Updated: 2019/08/20 12:19:07 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_insert(t_line *line, char c)
{
	int i;

	i = ft_strlen(line->str);
	while (i > line->pos)
	{
		line->str[i] = line->str[i - 1];
		i--;
	}
	CURSOR = c;
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