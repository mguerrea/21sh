/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:23:11 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/14 14:55:24 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_shell(char **environ)
{
	char **env;
	char **var;
	char *shlvl;

	env = NULL;
	if (!(env = ft_tabdup(env, environ)))
		return (NULL);
	if ((var = ft_getenv(env, "SHLVL")) && var[0])
	{
		if (ft_strcmp(var[0], "1"))
			ft_putstr_color("You appear to have launched a minishell \
inside another minishell.\n\
	--Welcome to minishellception !--\n", "green");
		shlvl = ft_itoa(ft_atoi(var[0]) + 1);
		ft_setvar(&env, "SHLVL", shlvl);
		free_tab(var);
		ft_strdel(&shlvl);
	}
	else
		ft_setvar(&env, "SHLVL", "2");
	return (env);
}

int		init_term(void)
{
	int		ret;
	char	*term_type;

	if ((term_type = getenv("TERM")) == NULL)
		return (-1);
	if ((ret = tgetent(NULL, term_type)) == -1)
		return (-1);
	if (!(g_term = (t_term *)malloc(sizeof(t_term))))
		return (-1);
	if (tcgetattr(0, &g_term->init) == -1)
		return (0);
	if (tcgetattr(0, &g_term->cur) == -1)
		return (-1);
	g_term->cur.c_lflag &= ~(ICANON | ECHO);
	g_term->cur.c_cc[VMIN] = 1;
	g_term->cur.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &g_term->cur) == -1)
		return (-1);
	return (1);
}
