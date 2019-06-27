/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:22:57 by mguerrea          #+#    #+#             */
/*   Updated: 2019/06/24 18:05:54 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void handle_child(int sig)
{
	if (sig == 2)
		kill(g_pid, 2);
}

void handle_parent(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		print_prompt();
	}
}

void catch_signals(int parent)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (parent)
		signal(SIGINT, handle_parent);
	else
		signal(SIGINT, handle_child);
}