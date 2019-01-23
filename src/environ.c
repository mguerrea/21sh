/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 16:45:44 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/23 16:56:21 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setvar(char ***environ, char *var, char *value)
{
	int		i;
	char	*str;

	i = 0;
	while ((*environ)[i] && ft_strncmp((*environ)[i], var, ft_strlen(var)))
		i++;
	if (!(str = ft_strnew(ft_strlen(var) + ft_strlen(value) + 1)))
		return ;
	ft_strcat(str, var);
	ft_strcat(str, "=");
	ft_strcat(str, value);
	if (!(*environ)[i])
		*environ = ft_addentry(*environ, i, str);
	else
	{
		ft_strdel(&((*environ)[i]));
		(*environ)[i] = ft_strdup(str);
	}
	ft_strdel(&str);
}

int		ft_setenv(t_cmdlst *cmd, char ***environ)
{
	pid_t pid;

	if ((pid = (cmd->pipes) ? do_pipe(cmd) : -1) > 0)
		return (1);
	if (cmd->args[1] && cmd->args[2])
	{
		if (ft_strchr(cmd->args[1], '='))
			ft_putendl("invalid name, cannot contain '='");
		else
			ft_setvar(environ, cmd->args[1], cmd->args[2]);
	}
	else
		ft_putendl("too few arguments");
	if (pid == 0)
		exit (1);
	return (1);
}

int		ft_unsetenv(t_cmdlst *cmd, char ***environ)
{
	int i;
	pid_t pid;

	i = 0;
	if ((pid = (cmd->pipes) ? do_pipe(cmd) : -1) > 0)
		return (1);
	if (cmd->args[1])
	{
		while ((*environ)[i] && ft_strncmp((*environ)[i], cmd->args[1],
			ft_strlen(cmd->args[1])))
			i++;
		if ((*environ)[i])
			ft_delentry(environ, i);
	}
	if (pid == 0)
		exit (1);
	return (1);
}

char	**ft_getenv(char **environ, char *var)
{
	int		i;
	char	**lst;
	int		len;

	i = 0;
	lst = NULL;
	len = ft_strlen(var);
	while (environ[i] && (ft_strncmp(environ[i], var, len)
		|| environ[i][len] != '='))
		i++;
	if (environ[i])
		lst = ft_strsplit(ft_strchr(environ[i], '=') + 1, ':');
	return (lst);
}
