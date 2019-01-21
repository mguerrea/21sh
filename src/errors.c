/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 19:56:10 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/08 11:42:42 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_file(char *cmd, char *errors)
{
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
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
}

void	error_rights(char *cmd, char *str)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": Permission denied", 2);
}

void	malloc_error(void)
{
	ft_putendl_fd("malloc error, abort program", 2);
	exit(EXIT_FAILURE);
}

int		error_args(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": too many arguments", 2);
	return (1);
}
