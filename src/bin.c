/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 19:18:45 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/23 13:48:36 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_bin_path(char **environ, char **args, char **path_lst)
{
	int			i;
	char		*path;
	struct stat	sb;

	i = 0;
	while (path_lst[i])
	{
		if (!(path = ft_strjoin3(path_lst[i], "/", args[0])))
			return ;
		if (lstat(path, &sb) == 0)
		{
			if (access(path, X_OK) != 0)
				error_rights(NULL, path);
			else
				execve(path, args, environ);
			ft_strdel(&path);
			break ;
		}
		ft_strdel(&path);
		i++;
	}
	if (path_lst[i] == NULL)
		error_cmd(args[0]);
	free_tab(path_lst);
}

int		launch_bin(t_cmdlst *cmd, char ***environ)
{
	pid_t	pid;
	int		i;
	char	**path_lst;

	i = 0;
	pid = fork();
	if (pid == -1)
		ft_putendl_fd("fork error", 2);
	else if (pid == 0)
	{
	//	do_pipe(cmd);
		if (cmd->pipes & PIPE_L)
		{
			dup2(cmd->prev->fd[0], STDIN_FILENO);
		}
		if (cmd->pipes & PIPE_R)
		{
			dup2(cmd->fd[1], STDOUT_FILENO);
		}
	//	close(cmd->fd[0]);
		if (ft_strchr(cmd->args[0], '/'))
		{
			if (execve(cmd->args[0], cmd->args, *environ) < 0)
				error_cmd(cmd->args[0]);
		}
		else if ((path_lst = ft_getenv(*environ, "PATH")))
			find_bin_path(*environ, cmd->args, path_lst);
		else
			error_cmd(cmd->args[0]);
		exit(1);
	}
	else
	{
		wait(NULL);
		close(cmd->fd[1]);
		if (cmd->prev)
			close(cmd->prev->fd[0]);
	/*	if (cmd->prev)
		{
			close(cmd->prev->fd[0]);
			close(cmd->prev->fd[1]);
		}*/
	}
	return (1);
}
