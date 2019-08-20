/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:37:29 by mguerrea          #+#    #+#             */
/*   Updated: 2019/08/20 14:48:11 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void manage_delete(char *buff, t_line *line)
{
	char *res;

	if (buff[0] == 127 && line->pos > 0)
		{
			move_left((&line->pos));
			res = tgetstr("dc", NULL); // delete
			tputs(res, 1, ft_print);
			ft_delete(line);
		}
}

int manage_endline(char *buff, t_line *line)
{
	if (buff[0] == '\n')
		{
			if (line->str[line->pos - 1] == '\\')
			{
				ft_putstr("\n> ");
				ft_delete(line);
				line->pos--;
			}
			else if (wrong_quote(line->str))
			{
				ft_putstr("\n> ");
				ft_insert(line, '\n');
				line->pos++;
			}
			else if (line->str[0] == 0)
			{
				ft_putchar('\n');
				print_prompt(&(line->pos));
			}
			else
				return (1);

		}
		return (0);
}

void manage_char(char *buff, t_line *line)
{
	if (buff[0] != 27 && buff[0] != 127 && buff[0] != '\n'
			&& line->pos < ARG_MAX && buff[0] != '\t')
		{
			ft_putstr(buff);
			ft_insert(line, buff[0]);
			line->pos++;
		}
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

int get_line(t_history **history)
{
	char buff[16];
	int ret;
	char *res;
	t_line line[1];

	if ((res = tgetstr("im", NULL)))
		tputs(res, 1, ft_print);
	print_prompt(&(line->pos));
	line->str = ft_strnew(ARG_MAX);
	catch_signals(1, line->str, &(line->pos));
	while ((ret = read(STDIN_FILENO, buff, 15)) > 0)
	{
		buff[ret] = 0;
		manage_pos(buff, line);
		manage_delete(buff, line);
		manage_history(buff, history, line);
		manage_char(buff, line);
		if (manage_endline(buff, line) || buff[0] == 4)
			break ;
	}
	ft_putchar('\n');
	return(save_history(history, &(line->str)));
}