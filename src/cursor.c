/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:32:29 by mguerrea          #+#    #+#             */
/*   Updated: 2019/08/20 15:17:21 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_right(int *pos)
{
	char *res;

	res = tgetstr("nd", NULL);
	tputs(res, 1, ft_print);
	(*pos)++;
}

void	move_left(int *pos)
{
	char *res;

	res = tgetstr("le", NULL);
	tputs(res, 1, ft_print);
	(*pos)--;
}

void manage_pos(char *buff, t_line *line)
{
	if (ft_strncmp(buff, "\033\033[C", 4) == 0) //opt right
	{
		while (CURSOR != ' ' && CURSOR)
			move_right(&(line->pos));
		while (CURSOR == ' ')
			move_right(&(line->pos));
	}
	if (ft_strncmp(buff, "\033\033[D", 4) == 0) // opt left
	{
		while (line->pos > 0 && line->str[line->pos - 1] == ' ')
			move_left(&(line->pos));
		while (line->pos > 0 && line->str[line->pos - 1] != ' ')
			move_left(&(line->pos));
	}
	if (ft_strncmp(buff, "\033[D", 3) == 0 && line->pos > 0)
		move_left(&(line->pos));
	else if (ft_strncmp(buff, "\033[C", 3) == 0 && CURSOR)
		move_right(&(line->pos));
	if (ft_strncmp(buff, "\033[F", 3) == 0) //end
		while (CURSOR)
			move_right(&(line->pos));
	if (ft_strncmp(buff, "\033[H", 3) == 0) //home
		while (line->pos > 0)
			move_left(&(line->pos));
}