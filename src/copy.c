/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:57:38 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 14:52:25 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_copy(t_line *line)
{
	char c;

	line->copy[0] = 0;
	tputs(tgetstr("mr", NULL), 0, ft_print);
	if (!CURSOR)
		move_left((&line->pos));
	c = line->str[line->pos];
	tputs(tgetstr("dc", NULL), 1, ft_print);
	ft_putchar(c);
	ft_strncat(line->copy, &c, 1);
	tputs(tgetstr("le", NULL), 1, ft_print);
}

void	manage_paste(char *buff, t_line *line)
{
	if (buff[0] == 5)
	{
		ft_putstr(line->copy);
		ft_strcat(line->str, line->copy);
		line->pos += ft_strlen(line->copy);
	}
}

void	manage_copy(char *buff, t_line *line)
{
	int		ret;
	char	new_buff[16];
	char	c;

	if (buff[0] == 2)
	{
		init_copy(line);
		while ((ret = read(STDIN_FILENO, new_buff, 15)) && new_buff[0] != 2)
		{
			new_buff[ret] = 0;
			if (ft_strncmp(new_buff, "\033[C", 3) == 0 && CURSOR)
			{
				move_right((&line->pos));
				c = line->str[line->pos];
				tputs(tgetstr("dc", NULL), 1, ft_print);
				ft_putchar(c);
				ft_strncat(line->copy, &c, 1);
				tputs(tgetstr("le", NULL), 1, ft_print);
			}
		}
		move_right((&line->pos));
		tputs(tgetstr("me", NULL), 0, ft_print);
	}
	manage_paste(buff, line);
}
