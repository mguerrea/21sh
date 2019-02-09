/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:37:54 by mguerrea          #+#    #+#             */
/*   Updated: 2019/02/09 17:46:35 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"
#include "sh_parser.h"

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
	char		*line;
	// char		**sargs;
	// char	**cmd;
	int			run;
	t_token		*tknlst;
	t_cmdlst	*cmd;

	run = 1;
	while (run)
	{
		if (!(line = get_cmd(*env)))
			break ;
		tknlst = tokenize_line(line);
		cmd = parse(tknlst);
		// cmd = split_quotes(line, ';');
		while (cmd)
		{
			// args = split_quotes(cmd[i], ' ');
			// format_args(&args, *env);
			format_args(cmd, *env);
			run = execute(cmd->args, builtin_lst, builtin_fct, env);
			// free_tab(args);
			cmd = cmd->next;
		}
		// free_tab(cmd);
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

// int main(int argc, char **argv)
// {
// 	t_token *tknlst;
// 	t_token *tmp;

// 	if (argc > 1)
// 	{
// 		tknlst = tokenize_line(argv[1]);
// 		tmp = tknlst;
// 		while (tmp)
// 		{
// 			ft_putstr(tmp->word);
// 			ft_putstr(" : ");
// 			ft_putnbr(tmp->type);
// 			ft_putchar('\n');
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (0);
// }
