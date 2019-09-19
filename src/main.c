/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:37:54 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/19 16:02:01 by mguerrea         ###   ########.fr       */
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
	pid_t pid;

	i = 0;
	ret = 1;
	cmd->exec = 1;
	while (i < NB_BUILTIN)
	{
		if (ft_strcmp(cmd->args[0], g_builtin_lst[i]) == 0)
			break ;
		i++;
	}
	if (((cmd->pipes & PIPE_R) && i < NB_BUILTIN) || i == NB_BUILTIN)
	{
		if ((pid = do_pipe(cmd, environ)) == -1)
			throw_error("fork error");
		if (pid == 0)
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
		if (cmd->exec == 0)
		{
		if (!(saved = save_fd(cmd)))
			malloc_error();
		format_args(cmd, *env);
		create_files(cmd);
		run = execute(cmd, env);
		restore_fd(cmd, saved);
		}
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

	tknlst = NULL;
	cmd = NULL;
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
		tkn_lst_del(&tknlst);
		run = iter_cmd(cmd, run, env);
		free_cmdlst(&cmd);
	}
	free_history(&history);
	return (0);
}

int		main(int argc, char **argv, char **environ)
{
	char		**env;
	int			ret;

	(void)argc;
	(void)argv;
	g_term = NULL;
	g_pid[0] = -2;
	if ((ret = init_term()) == -1)
		return (throw_error("seems like you did not send us a proper env"));
	else if (ret == 0)
	{
		ft_putendl("Non interactive mode");
		free(g_term);
		g_term = NULL;
	}
	if (!(env = init_shell(environ)))
		return (throw_error("malloc error"));
	run(&env);
	free_tab(env);
	tcsetattr(0, TCSANOW, &g_term->init);
	return (0);
}
