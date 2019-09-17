/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:03:40 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/14 14:19:22 by mguerrea         ###   ########.fr       */
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
	if (*history)
	{
		if ((*history)->next)
			free_history(&(*history)->next);
		ft_strdel(&((*history)->line));
	}
}