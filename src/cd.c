/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:40:08 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/09 15:57:05 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*format_dir(char **args, char ***environ)
{
	char *dir;
	char **var;

	dir = NULL;
	if (args[1] == NULL)
	{
		if (!(var = ft_getenv(*environ, "HOME")))
			dir = ft_strdup(getpwuid(getuid())->pw_dir);
		else
			dir = ft_strdup(var[0]);
		free_tab(var);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (!(var = ft_getenv(*environ, "OLDPWD"))
			|| !(dir = ft_strdup(var[0])))
			ft_putendl("cd: OLDPWD not set");
		else
			ft_putendl(dir);
		free_tab(var);
	}
	else
		dir = ft_strdup(args[1]);
	return (dir);
}

int		ft_cd(t_cmdlst *cmd, char ***environ)
{
	char		*dir;
	char		buf[PATH_MAX];
	struct stat	sb;
//	pid_t		pid;

//	if ((pid = (cmd->pipes) ? do_pipe(cmd) : -2) > 0)
//		return (1);
//	if (pid == -1)
//		return (throw_error("fork error"));
	if (redirection(cmd) == -1)
	{
//		if (pid == 0)
//			exit(1);
//		else
			return (1);
	}
	if (cmd->args[1] && cmd->args[2])
		return (error_args("cd"));
	dir = format_dir(cmd->args, environ);
	getcwd(buf, PATH_MAX);
	ft_setvar(environ, "OLDPWD", buf);
	if (dir && lstat(dir, &sb) == 0)
	{
		if (access(dir, X_OK) != 0)
			error_rights("cd", dir);
		chdir(dir);
	}
	else if (dir)
		error_file("cd", dir);
	getcwd(buf, PATH_MAX);
	ft_setvar(environ, "PWD", buf);
	if (dir)
		ft_strdel(&dir);
//	if (pid == 0)
//		exit(1);
	return (1);
}
