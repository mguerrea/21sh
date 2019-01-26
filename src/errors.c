/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 19:56:10 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/26 16:54:49 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_file(char *cmd, char *errors)
{
	ft_putstr("21sh: ");
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(errors, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	error_cmd(char *str)
{
	ft_putstr("21sh: ");
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
}

void	error_fd(int fd)
{
	ft_putstr("21sh: ");
	ft_putnbr_fd(fd, 2);
	ft_putendl_fd(": Bad file descriptor", 2);
}

void	error_rights(char *cmd, char *str)
{
	ft_putstr("21sh: ");
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": Permission denied", 2);
}

int		throw_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (0);
}

void	malloc_error(void)
{
	ft_putendl_fd("malloc error, abort program", 2);
	exit(EXIT_FAILURE);
}

int		error_args(char *cmd)
{
	ft_putstr("21sh: ");
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": too many arguments", 2);
	return (1);
}