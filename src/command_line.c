/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:37:29 by mguerrea          #+#    #+#             */
/*   Updated: 2019/04/19 13:20:38 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void manage_arrows(int *pos, char *buff, char *line)
{
	char *res;

	if (strncmp(buff, "\033[D", 3) == 0 && *pos > 0)
		{
			res = tgetstr("le", NULL); // move left
			tputs(res, 1, ft_print);
			(*pos)--;
		}
		else if (strncmp(buff, "\033[C", 3) == 0 && line[*pos])
		{
			res = tgetstr("nd", NULL); // move right
			tputs(res, 1, ft_print);
			(*pos)++;
		}
}

void manage_delete(int *pos, char *buff, char *line)
{
	char *res;

	if (buff[0] == 127 && *pos > 0)
		{
			res = tgetstr("le", NULL); // move left
			tputs(res, 1, ft_print);
			res = tgetstr("dc", NULL); // delete
			tputs(res, 1, ft_print);
			(*pos)--;
			ft_delete(line, *pos);
		}
}

int manage_endline(int *pos, char *buff, char *line)
{
	if (buff[0] == '\n')
		{
			if (line[*pos - 1] == '\\')
			{
				ft_putstr("\n> ");
				ft_delete(line, *pos - 1);
				(*pos)--;
			}
			else if (wrong_quote(line))
			{
				ft_putstr("\n> ");
				ft_insert(line, '\n', *pos);
				(*pos)++;
			}		
			else
				return (1);
		}
		return (0);
}

void manage_char(int *pos, char *buff, char *line)
{
	if (buff[0] != 27 && buff[0] != 127 && buff[0] != '\n' && *pos < ARG_MAX)
		{
			ft_putstr(buff);
			ft_insert(line, buff[0], *pos);
			(*pos)++;
		}
}

void get_line(t_history *history)
{
	char buff[16];
	int ret;
	char *res;
	int pos;
	char *line;

	pos = 0;
	if ((res = tgetstr("im", NULL)))
		tputs(res, 1, ft_print);
	print_prompt();
	line = ft_strnew(ARG_MAX);
	while ((ret = read(STDIN_FILENO, buff, 15)) > 0)
	{
		buff[ret] = 0;
		manage_arrows(&pos, buff, line);
		manage_delete(&pos, buff, line);
		manage_history(buff, &history, line, &pos);
		if (manage_endline(&pos, buff, line))
			break ;
		manage_char(&pos, buff, line);
	}
	save_history(history, &line);
}