/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:37:29 by mguerrea          #+#    #+#             */
/*   Updated: 2019/04/13 17:51:53 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_print(int c)
{
	ft_putchar(c);
	return(1);
}

void manage_arrows(int *pos, char *buff, t_history *history, char **env)
{
	char *res;

/*	if (strncmp(buff, "\033[A", 3) == 0 && history->prev) //up
		{
			ft_putchar('U');
			res = tgetstr("dl", NULL); // del line
			tputs(res, 1, ft_print);
			history = history->prev;
			res = tgetstr("cr", NULL); // move at the start
			tputs(res, 1, ft_print);
			print_prompt(env);
			ft_putstr(history->line);
		}*/
	if (strncmp(buff, "\033[D", 3) == 0 && *pos > 0)
		{
			res = tgetstr("le", NULL); // move left
			tputs(res, 1, ft_print);
			(*pos)--;
		}
		else if (strncmp(buff, "\033[C", 3) == 0 && history->line[*pos])
		{
			res = tgetstr("nd", NULL); // move right
			tputs(res, 1, ft_print);
			(*pos)++;
		}
}

void manage_delete(int *pos, char *buff, t_history *history)
{
	char *res;

	if (buff[0] == 127 && *pos > 0)
		{
			res = tgetstr("le", NULL); // move left
			tputs(res, 1, ft_print);
			res = tgetstr("dc", NULL); // delete
			tputs(res, 1, ft_print);
			(*pos)--;
			ft_delete(history->line, *pos);
		}
}

int manage_endline(int *pos, char *buff, t_history *history)
{
	if (buff[0] == '\n')
		{
			if (history->line[*pos - 1] == '\\')
			{
				ft_putstr("\n> ");
				ft_delete(history->line, *pos - 1);
				(*pos)--;
			}
			else if (wrong_quote(history->line))
			{
				ft_putstr("\n> ");
				ft_insert(history->line, '\n', *pos);
				(*pos)++;
			}		
			else
				return (1);
		}
		return (0);
}

void manage_char(int *pos, char *buff, t_history *history)
{
	if (buff[0] != 27 && buff[0] != 127 && buff[0] != '\n' && *pos < ARG_MAX)
		{
			ft_putstr(buff);
			ft_insert(history->line, buff[0], *pos);
			(*pos)++;
		}
}

void manage_history(char *buff, t_history *history, char **env)
{
	char *res;

	if (strncmp(buff, "\033[A", 3) == 0 && history->prev) //up
		{
			ft_putchar('U');
			res = tgetstr("dl", NULL); // del line
			tputs(res, 1, ft_print);
			history = history->prev;
			res = tgetstr("cr", NULL); // move at the start
			tputs(res, 1, ft_print);
			print_prompt(env);
			ft_putstr(history->line);
		}
}

void get_line(t_history *history, char **env)
{
	char buff[16];
	int ret;
	char *res;
	int pos;
	char *line;

	pos = 0;
	res = tgetstr("im", NULL);
	tputs(res, 1, ft_print);
	print_prompt(env);
	line = ft_strnew(ARG_MAX);
	while (1)
	{
		
		ret = read(STDIN_FILENO, buff, 15);
		buff[ret] = 0;
		manage_arrows(&pos, buff, history, env);
		manage_delete(&pos, buff, history);
		manage_history(buff, history, env);
		if (manage_endline(&pos, buff, history))
			break ;
		manage_char(&pos, buff, history);
	}
	res = tgetstr("ei", NULL);
	tputs(res, 1, ft_print);
}