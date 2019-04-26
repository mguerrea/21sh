/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:37:54 by mguerrea          #+#    #+#             */
/*   Updated: 2019/04/26 16:18:23 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"
#include "sh_parser.h"

int		execute(t_cmdlst *cmd, const char **builtin_lst,
	t_built_in *builtin_fct, char ***environ)
{
	int i;

	i = 0;
	if (pipe(cmd->fd) == -1)
		return (0);
	// ft_putendl(cmd->args[0]);
	// ft_putendl(cmd->args[1]);
	// ft_putnbr(cmd->pipes);
	// ft_putchar('\n');
	while (i < NB_BUILTIN)
	{
		if (ft_strcmp(cmd->args[0], builtin_lst[i]) == 0)
			return (builtin_fct[i](cmd, environ));
		i++;
	}
	return (launch_bin(cmd, environ));
}

int	run(char ***env, t_built_in *builtin_fct, const char **builtin_lst)
{
	int			run;
	t_token		*tknlst;
	t_cmdlst	*cmd;
	int			saved;
	t_history *history;

	history = NULL;
	run = 1;
	while (run)
	{
		if(!(add_to_history(&history)))
			return (-1);
		get_line(&history);
		tknlst = tokenize_line(history->line);
		cmd = parse(tknlst);
		while (cmd)
		{
			saved = dup(cmd->redir[1].fd[0]);
			format_args(cmd, *env);
			run = execute(cmd, builtin_lst, builtin_fct, env);
			dup2(saved, cmd->redir[1].fd[0]);
			cmd = cmd->next;
		}
		// we have to free cmd
	}
	// we have to free history
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
	t_term		*term;

	(void)argc;
	(void)argv;
	term = NULL;
	term = init_term(term);
	
	if (!(env = init_shell(environ, builtin_fct)))
		return (throw_error("malloc error"));
	run(&env, builtin_fct, builtin_lst);
	free_tab(env);
	tcsetattr(0, TCSANOW, &term->init);
	return (0);
}
