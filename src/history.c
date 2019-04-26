/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:58:17 by mguerrea          #+#    #+#             */
/*   Updated: 2019/04/26 16:18:19 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_history(t_history **history, char **line)
{
	char *res;

	while ((*history)->next)
		*history = (*history)->next;
	ft_strcpy((*history)->line, *line);
	ft_strdel(line);
	if ((res = tgetstr("ei", NULL)))
		tputs(res, 1, ft_print);
}

void manage_history(char *buff, t_history **history, char *line, int *pos)
{
	char *res;

	if ((strncmp(buff, "\033[A", 3) == 0 && (*history)->prev)
			|| (strncmp(buff, "\033[B", 3) == 0 && (*history)->next))
	{
		res = tgetstr("dl", NULL); // del line
		tputs(res, 1, ft_print);
		if (ft_strncmp(buff, "\033[A", 3) == 0) //up
		{
			if ((*history)->next == NULL)
				ft_strcpy((*history)->line, line);
			*history = (*history)->prev;
		}
		else
			*history = (*history)->next;
		res = tgetstr("cr", NULL); // move at the start
		tputs(res, 1, ft_print);
		print_prompt();
		ft_putstr((*history)->line);
		ft_bzero(line, ARG_MAX + 1);
		ft_strcpy(line, (*history)->line);
		*pos = ft_strlen(line);
	}
}

t_history *add_to_history(t_history **history)
{
	t_history *new;

	if(!(new = (t_history *)malloc(sizeof(t_history))))
			return (NULL);
	if(!(new->line = ft_strnew(ARG_MAX)))
		return (NULL);
	new->next = NULL;
	new->prev = *history;
	if (*history == NULL)
		*history = new;
	else
	{
		(*history)->next = new;
		*history = (*history)->next;
	}
	return (*history);
}