/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:37:54 by mguerrea          #+#    #+#             */
/*   Updated: 2019/06/24 11:48:45 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"
#include "sh_parser.h"

int		execute(t_cmdlst *cmd, const char **builtin_lst,
	t_built_in *builtin_fct, char ***environ)
{
	int i;
	int ret;
	pid_t pid;

	i = 0;
	ret = 1;
	while (i < NB_BUILTIN)
	{
		if (ft_strcmp(cmd->args[0], builtin_lst[i]) == 0)
			break ;
		i++;
	}
	if (((cmd->pipes & PIPE_R) && i < NB_BUILTIN) || i == NB_BUILTIN)
	{
		if ((pid = do_pipe(cmd)) == -1)
			throw_error("fork error");
		if (pid == 0)
		{
			if (i < NB_BUILTIN)
				ret = builtin_fct[i](cmd, environ);
			else
				ret = launch_bin(cmd, environ);
			exit (0);
		}
	}
	else
		ret = builtin_fct[i](cmd, environ);
	return (ret);
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
			close(saved);
			cmd = cmd->next;
		}
		// we have to free cmd and tknlst
	}
	free_history(&history);
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
