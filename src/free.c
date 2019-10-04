/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:03:40 by mguerrea          #+#    #+#             */
/*   Updated: 2019/10/04 16:32:34 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **array)
{
	int i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		ft_strdel(&(array[i]));
		i++;
	}
	free(array);
}

void	free_history(t_history **history)
{
	t_history *tmp;

	if (*history)
	{
		while ((*history)->prev)
			*history = (*history)->prev;
		while (*history)
		{
			tmp = *history;
			(*history) = (*history)->next;
			ft_strdel(&(tmp->line));
			free(tmp);
		}
	}
}
