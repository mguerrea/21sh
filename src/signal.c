/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:22:57 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/20 17:22:26 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *g_line = NULL;
int *g_pos;

void	handle_child(int sig)
{
	int i;

	i = 0;
	while (g_pid[i] != -2)
		i++;
	if (sig == 2)
	{
		kill(g_pid[i - 1], 2);
		ft_putchar_fd('\n', 0);
	}
}

void	handle_parent(int sig)
{
	if (sig == SIGINT)
	{
		ft_bzero(g_line, ARG_MAX);
		ft_putchar('\n');
		print_prompt(g_pos);
	}
}

void	catch_signals(int parent, char *str, int *pos)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (parent)
	{
		g_line = str;
		g_pos = pos;
		signal(SIGINT, handle_parent);
	}
	else
		signal(SIGINT, handle_child);
}
