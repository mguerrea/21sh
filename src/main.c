/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:37:54 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 15:37:35 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh_parser.h"

const char		*g_builtin_lst[] = {"cd", "exit", "echo", "env", "setenv",
	"unsetenv"};
const t_built_in g_builtin_fct[] = {ft_cd, ft_exit, ft_echo, ft_env,
	ft_setenv, ft_unsetenv};

int		execute(t_cmdlst *cmd, char ***environ)
{
	int i;
	int ret;

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
		if ((g_pid = do_pipe(cmd)) == -1)
			throw_error("fork error");
		if (g_pid == 0)
		{
			ret = (i < NB_BUILTIN) ? g_builtin_fct[i](cmd, environ) :
				launch_bin(cmd, environ);
			exit(0);
		}
	}
	else
		ret = g_builtin_fct[i](cmd, environ);
	return (ret);
}

int		iter_cmd(t_cmdlst *cmd, int run, char ***env)
{
	int *saved;

	while (cmd && run)
	{
		if (!(saved = save_fd(cmd)))
			malloc_error();
		format_args(cmd, *env);
		create_files(cmd);
		run = execute(cmd, env);
		restore_fd(cmd, saved);
		cmd = cmd->next;
	}
	return (run);
}

int		run(char ***env)
{
	int			run;
	t_token		*tknlst;
	t_cmdlst	*cmd;
	t_history	*history;

	history = NULL;
	run = 1;
	while (run)
	{
		if (!(add_to_history(&history)))
			return (-1);
		if (get_line(&history) == 0 || history->line[0] == 0)
			break ;
		tknlst = tokenize_line(history->line);
		cmd = parse(tknlst);
		run = iter_cmd(cmd, run, env);
		// we have to free cmd and tknlst
	}
	free_history(&history);
	return (0);
}

int		main(int argc, char **argv, char **environ)
{
	char		**env;

	(void)argc;
	(void)argv;
	g_term = NULL;
	if (!(g_term = init_term(g_term)))
		return (throw_error("seems like you did not send us a proper env"));
	if (!(env = init_shell(environ)))
		return (throw_error("malloc error"));
	run(&env);
	free_tab(env);
	tcsetattr(0, TCSANOW, &g_term->init);
	return (0);
}
