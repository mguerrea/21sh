/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 19:56:10 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/20 15:11:49 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_file(char *cmd, char *errors)
{
	if (access(errors, X_OK) != 0)
		error_rights(NULL, errors);
	else
	{
		ft_putstr_fd("21sh: ", 2);
		if (cmd)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd(errors, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (-1);
}

void	error_cmd(char *str)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
}

int		error_fd(int fd)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putnbr_fd(fd, 2);
	ft_putendl_fd(": Bad file descriptor", 2);
	return (-1);
}

void	error_rights(char *cmd, char *str)
{
	ft_putstr_fd("21sh: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": Permission denied", 2);
}

int		error_args(char *cmd)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": too many arguments", 2);
	return (1);
}
