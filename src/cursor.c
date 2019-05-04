/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:32:29 by mguerrea          #+#    #+#             */
/*   Updated: 2019/05/04 14:37:51 by mguerrea         ###   ########.fr       */
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