/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 13:24:23 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/06 17:36:39 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_quotes(char *line, char c)
{
	int i;
	int count;
	int quote;
	int is_word;

	i = 0;
	quote = 0;
	count = 1;
	is_word = 0;
	while (line[i])
	{
		if (line[i] == '"')
			quote++;
		if (line[i] != c && is_word == 0 && quote % 2 == 0)
		{
			is_word = 1;
			count++;
		}
		if (line[i] == c && is_word == 1)
			is_word = 0;
		i++;
	}
	return (count);
}

int		count_letters(char *line, char c)
{
	int i;
	int quote;

	i = 0;
	quote = 0;
	while ((line[i] != c || quote % 2 == 1) && line[i])
	{
		if (line[i] == '"')
			quote++;
		i++;
	}
	return (i);
}

char	**split_quotes(char *line, char c)
{
	char	**cmd;
	int		j;

	j = 0;
	if (!(cmd = (char **)malloc(sizeof(char *) * (count_quotes(line, c) + 1))))
		return (NULL);
	while (*line)
	{
		while (*line == c)
			line++;
		if (*line == '\0')
			break ;
		if (!(cmd[j] = ft_strsub((char *)line, 0, count_letters(line, c))))
			return (NULL);
		line += (count_letters(line, c));
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}
