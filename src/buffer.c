/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:50:08 by mguerrea          #+#    #+#             */
/*   Updated: 2019/04/10 15:04:53 by mguerrea         ###   ########.fr       */
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

void ft_delete(char *line, int pos)
{
	int len;

	len = ft_strlen(line);
	while (pos < len)
	{
		line[pos] = line[pos + 1];
		pos++;
	}
}