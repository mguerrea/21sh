/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:37:29 by mguerrea          #+#    #+#             */
/*   Updated: 2019/07/01 14:52:30 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void manage_delete(int *pos, char *buff, char *line)
{
	char *res;

	if (buff[0] == 127 && *pos > 0)
		{
			move_left(pos);
			res = tgetstr("dc", NULL); // delete
			tputs(res, 1, ft_print);
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
	if (buff[0] != 27 && buff[0] != 127 && buff[0] != '\n' && *pos < ARG_MAX
			&& buff[0] != '\t')
		{
			ft_putstr(buff);
			ft_insert(line, buff[0], *pos);
			(*pos)++;
		}
}

void manage_pos(int *pos, char *buff, char *line)
{
	if (ft_strncmp(buff, "\033\033[C", 4) == 0) //opt right
	{
		while (line[*pos] != ' ' && line[*pos])
			move_right(pos);
		while (line[*pos] == ' ')
			move_right(pos);
	}
	if (ft_strncmp(buff, "\033\033[D", 4) == 0) // opt left
	{
		while (*pos > 0 && line[*pos - 1] == ' ')
			move_left(pos);
		while (*pos > 0 && line[*pos - 1] != ' ')
			move_left(pos);
	}
	if (ft_strncmp(buff, "\033[D", 3) == 0 && *pos > 0)
		move_left(pos);
	else if (ft_strncmp(buff, "\033[C", 3) == 0 && line[*pos])
		move_right(pos);
	if (ft_strncmp(buff, "\033[F", 3) == 0) //end
		while (line[*pos])
			move_right(pos);
	if (ft_strncmp(buff, "\033[H", 3) == 0) //home
		while (*pos > 0)
			move_left(pos);
}

int get_line(t_history **history)
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
		manage_pos(&pos, buff, line);
		manage_delete(&pos, buff, line);
		manage_history(buff, history, line, &pos);
		manage_char(&pos, buff, line);
		if (manage_endline(&pos, buff, line) || buff[0] == 4)
			break ;
	}
	ft_putchar('\n');
	return(save_history(history, &line));
}