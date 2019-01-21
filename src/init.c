/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:23:11 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/06 17:21:55 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_built(t_built_in *builtin_fct)
{
	builtin_fct[0] = ft_cd;
	builtin_fct[1] = ft_exit;
	builtin_fct[2] = ft_echo;
	builtin_fct[3] = ft_env;
	builtin_fct[4] = ft_setenv;
	builtin_fct[5] = ft_unsetenv;
}

char	**init_shell(char **environ, t_built_in *builtin_fct)
{
	char **env;
	char **var;
	char *shlvl;

	env = NULL;
	fill_built(builtin_fct);
	if (!(env = ft_tabdup(env, environ)))
		malloc_error();
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
