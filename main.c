/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:37:54 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/06 17:29:10 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include "minishell.h"

int	execute(char **args, const char **builtin_lst,
	t_built_in *builtin_fct, char ***environ)
{
	int i;

	i = 0;
	if (args[0] == NULL)
		return (1);
	while (i < NB_BUILTIN)
	{
		if (ft_strcmp(args[0], builtin_lst[i]) == 0)
			return (builtin_fct[i](args, environ));
		i++;
	}
	return (launch_bin(args, environ));
}

int	run(char ***env, t_built_in *builtin_fct, const char **builtin_lst)
{
	char	*line;
	char	**args;
	char	**cmd;
	int		run;
	int		i;

	run = 1;
	while (run)
	{
		i = 0;
		line = get_cmd(*env);
		cmd = split_quotes(line, ';');
		while (cmd[i])
		{
			args = split_quotes(cmd[i], ' ');
			format_args(&args, *env);
			run = execute(args, builtin_lst, builtin_fct, env);
			i++;
			free_tab(args);
		}
		free_tab(cmd);
		ft_strdel(&line);
	}
	return (0);
}

int	main(int argc, char **argv, char **environ)
{
	char		**env;
	t_built_in	builtin_fct[NB_BUILTIN];
	const char	*builtin_lst[] = {
		"cd",
		"exit",
		"echo",
		"env",
		"setenv",
		"unsetenv"
	};

	(void)argc;
	(void)argv;
	env = init_shell(environ, builtin_fct);
	run(&env, builtin_fct, builtin_lst);
	free_tab(env);
	return (0);
}
