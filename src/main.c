/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:37:54 by mguerrea          #+#    #+#             */
/*   Updated: 2019/07/01 12:37:50 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh_parser.h"

const char	*g_builtin_lst[] = {"cd", "exit", "echo", "env", "setenv",
	"unsetenv"};
const t_built_in g_builtin_fct[] = {ft_cd, ft_exit, ft_echo, ft_env,
	ft_setenv, ft_unsetenv};

int		execute(t_cmdlst *cmd, char ***environ)
{
	int i;
	int ret;
	pid_t pid;

	i = 0;
	ret = 1;
	while (i < NB_BUILTIN)
	{
		if (ft_strcmp(cmd->args[0], g_builtin_lst[i]) == 0)
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
				ret = g_builtin_fct[i](cmd, environ);
			else
				ret = launch_bin(cmd, environ);
			exit (0);
		}
	}
	else
		ret = g_builtin_fct[i](cmd, environ);
	return (ret);
}

int	run(char ***env)
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
		catch_signals(1);
		get_line(&history);
		tknlst = tokenize_line(history->line);
		cmd = parse(tknlst);
		while (cmd)
		{
			saved = dup(cmd->redir[1].fd[0]);
			format_args(cmd, *env);
			run = execute(cmd, env);
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

	(void)argc;
	(void)argv;
	g_term = NULL;
	g_term = init_term(g_term);
	if (!(env = init_shell(environ)))
		return (throw_error("malloc error"));
	run(&env);
	free_tab(env);
	tcsetattr(0, TCSANOW, &g_term->init);
	return (0);
}
