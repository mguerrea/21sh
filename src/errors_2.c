/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:55:25 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 14:56:03 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
