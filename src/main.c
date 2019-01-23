/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:37:54 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/23 16:42:51 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

/*int	execute(char **args, const char **builtin_lst,
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
}*/

#include <stdio.h>

int		execute_test(t_cmdlst *cmd, const char **builtin_lst,
	t_built_in *builtin_fct, char ***environ)
{
	int i;

	i = 0;
	if (cmd->pipes && pipe(cmd->fd) == -1)
		return (0);
	while (i < NB_BUILTIN)
	{
		if (ft_strcmp(cmd->args[0], builtin_lst[i]) == 0)
			return (builtin_fct[i](cmd, environ));
		i++;
	}
	return (launch_bin(cmd, environ));
}

/*int	run(char ***env, t_built_in *builtin_fct, const char **builtin_lst)
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
		if (!(line = get_cmd(*env)))
			break ;
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
}*/

/*int	main(int argc, char **argv, char **environ)
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
}*/

int main(int argc, char **argv, char **environ)
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
	t_cmdlst *cmd1;
	t_cmdlst *cmd2;
	t_cmdlst *cmd3;

	env = init_shell(environ, builtin_fct);
	cmd1 = (t_cmdlst *)malloc(sizeof(t_cmdlst));
	cmd2 = (t_cmdlst *)malloc(sizeof(t_cmdlst));
	cmd3 = (t_cmdlst *)malloc(sizeof(t_cmdlst));
	cmd1->args = (char **)malloc(sizeof(char *) * 4);
//	cmd1->args[0] = "ls";
//	cmd1->args[0] = "echo";
	cmd1->args[0] = "env";
//	cmd1->args[1] = "-l";
	cmd1->args[1] = NULL;
	cmd1->args[2] = "hello";
	cmd1->args[3] = NULL;
	cmd1->pipes = PIPE_R;
	cmd1->prev = NULL;
	cmd1->next = cmd2;
	cmd2->next = cmd3;
	cmd2->prev = cmd1;
	cmd2->args = (char **)malloc(sizeof(char *) * 4);
	cmd2->args[0] = "grep";
//	cmd2->args[0] = "cat";
	cmd2->args[1] = "HOME";
//	cmd2->args[1] = "-e";
	cmd2->args[2] = NULL;
	cmd2->pipes = PIPE_L | PIPE_R;
	cmd3->args = (char **)malloc(sizeof(char *) * 4);
	cmd3->prev = cmd2;
	cmd3->next = NULL;
	cmd3->args[0] = "wc";
	cmd3->args[1] = "-c";
	cmd3->args[2] = NULL;
	cmd3->pipes = PIPE_L;
	while (cmd1)
	{
//		printf("loop\n");
		ft_putendl(cmd1->args[0]);
		execute_test(cmd1, builtin_lst, builtin_fct, &env);
		cmd1 = cmd1->next;
	}
//	printf ("return ?\n");
	return (0);
}
