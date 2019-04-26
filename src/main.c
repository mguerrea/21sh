/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:37:54 by mguerrea          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/13 16:24:44 by gmichaud         ###   ########.fr       */
=======
/*   Updated: 2019/04/19 12:56:28 by mguerrea         ###   ########.fr       */
>>>>>>> termcaps
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
	char		*line;
	// char		**sargs;
	// char	**cmd;
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
		get_line(history);
		ft_putchar('\n');
		line = history->line;
	//	if (!(line = get_cmd(*env)))
	//		break ;
		tknlst = tokenize_line(line);
		cmd = parse(tknlst);
		// cmd = split_quotes(line, ';');
		while (cmd)
		{
			saved = dup(cmd->redir[1].fd[0]);
			// args = split_quotes(cmd[i], ' ');
			// format_args(&args, *env);
			format_args(cmd, *env);
			run = execute(cmd, builtin_lst, builtin_fct, env);
			// free_tab(args);
			dup2(saved, cmd->redir[1].fd[0]);
			cmd = cmd->next;
		}
		// free_tab(cmd);
//		ft_strdel(&line);
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
	term = NULL;
	term = init_term(term);
	
	if (!(env = init_shell(environ, builtin_fct)))
		return (throw_error("malloc error"));
	run(&env, builtin_fct, builtin_lst);
	free_tab(env);
	tcsetattr(0, TCSANOW, &term->init);
	return (0);
}

t_history *add_to_history(t_history **history)
{
	t_history *new;

	if(!(new = (t_history *)malloc(sizeof(t_history))))
			return (NULL);
	if(!(new->line = ft_strnew(ARG_MAX)))
		return (NULL);
	new->next = NULL;
	new->prev = *history;
	if (*history == NULL)
		*history = new;
	else
		(*history)->next = new;
	return (*history);
}


int main(int argc, char **argv, char **environ)
{
	char		**env;
	t_term		*term;
	t_built_in	builtin_fct[NB_BUILTIN];
	const char	*builtin_lst[] = {
		"cd",
		"exit",
		"echo",
		"env",
		"setenv",
		"unsetenv"
	};
	t_history *history;
	int saved;

	term = NULL;
	term = init_term(term);
	env = init_shell(environ, builtin_fct);

	history = NULL;
	

		if(!(add_to_history(&history)))
			return (-1);
		get_line(history);
		ft_putchar('\n');	

	if(!(add_to_history(&history)))
			return (-1);
	history = history->next;
		get_line(history);
		ft_putchar('\n');

		if(!(add_to_history(&history)))
			return (-1);
		history = history->next;
		get_line(history);
		ft_putchar('\n');

		if(!(add_to_history(&history)))
			return (-1);
		history = history->next;
		get_line(history);
		ft_putchar('\n');

	while (history->prev)
		history = history->prev;
	while (history)
	{
		ft_putendl(history->line);
		history = history->next;
	}
	tcsetattr(0, TCSANOW, &term->init);


