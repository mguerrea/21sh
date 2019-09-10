/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:54:28 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 14:34:50 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmdlst *cmd, char ***environ)
{
	(void)environ;
	(void)cmd;
	return (0);
}

int	ft_echo(t_cmdlst *cmd, char ***environ)
{
	int i;
	int n;

	(void)environ;
	if (redirection(cmd) == -1)
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
	return (1);
}

int	ft_env(t_cmdlst *cmd, char ***environ)
{
	int		i;
	char	**tmp;

	i = 0;
	if (redirection(cmd) == -1)
		return (1);
	if (cmd->args[1] == NULL)
		while ((*environ)[i])
			ft_putendl((*environ)[i++]);
	else
	{
		ft_delentry(&(cmd->args), 0);
		if (ft_strcmp(cmd->args[0], "-i") == 0)
		{
			if (!(tmp = (char **)malloc(sizeof(char *))))
				return (throw_error("malloc error"));
			tmp[0] = NULL;
			ft_delentry(&(cmd->args), 0);
			execute(cmd, &tmp);
			free(tmp);
		}
		else
			execute(cmd, environ);
	}
	return (1);
}
