/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:54:28 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/23 16:46:04 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmdlst *cmd, char ***environ)
{
	pid_t pid;

	if ((pid = (cmd->pipes) ? do_pipe(cmd) : -1) > 0)
		return (1);
	(void)environ;
	if (pid == 0)
		exit (1);
	return (0);
}

int	ft_echo(t_cmdlst *cmd, char ***environ)
{
	int i;
	int n;
	pid_t pid;

	(void)environ;
	if ((pid = (cmd->pipes) ? do_pipe(cmd) : -1) > 0)
		return (1);
	n = (cmd->args[1]) ? ft_strcmp(cmd->args[1], "-n") : 1;
	i = (n == 0) ? 2 : 1;
	while (cmd->args[i])
	{
		if (i > 2 || (i > 1 && n != 0))
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		i++;
	}
	if (n != 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (pid == 0)
		exit(1);
	return (1);
}

int	ft_env(t_cmdlst *cmd, char ***environ)
{
	int		i;
	char	**tmp;
	pid_t	pid;

	i = 0;
	if ((pid = (cmd->pipes) ? do_pipe(cmd) : -1) > 0)
		return (1);
	if (cmd->args[1] == NULL)
	{
		while ((*environ)[i])
			ft_putendl((*environ)[i++]);
	}
	else
	{
		ft_delentry(&(cmd->args), 0);
		if (ft_strcmp(cmd->args[0], "-i") == 0)
		{
			if (!(tmp = (char **)malloc(sizeof(char *))))
				malloc_error();
			tmp[0] = NULL;
			ft_delentry(&(cmd->args), 1);
			launch_bin(cmd, &tmp);
			free(tmp);
		}
		else
			launch_bin(cmd, environ);
	}
	if (pid == 0)
		exit (1);
	return (1);
}
