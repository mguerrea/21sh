/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:23:11 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 14:58:11 by mguerrea         ###   ########.fr       */
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

t_term	*init_term(t_term *term)
{
	int		ret;
	char	*term_type;

	if ((term_type = getenv("TERM")) == NULL)
		return (NULL);
	if ((ret = tgetent(NULL, term_type)) == -1)
		return (NULL);
	if (!(term = (t_term *)malloc(sizeof(t_term))))
		return (NULL);
	if (tcgetattr(0, &term->init) == -1)
		return (NULL);
	if (tcgetattr(0, &term->cur) == -1)
		return (NULL);
	term->cur.c_lflag &= ~(ICANON | ECHO);
	term->cur.c_cc[VMIN] = 1;
	term->cur.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term->cur) == -1)
		return (NULL);
	return (term);
}
