/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:52:40 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/10 15:53:44 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cmd_lst_push(t_cmdlst **lst, t_cmdlst *cmd)
{
	if (lst && cmd)
	{
		if (*lst)
			(*lst)->prev = cmd;
		cmd->next = *lst;
		*lst = cmd;
	}
}

void		cmd_lst_append(t_cmdlst **lst, t_cmdlst *cmd)
{
	t_cmdlst *tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = cmd;
	}
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
		cmd->prev = tmp;
	}
}

t_cmdlst	*cmd_lst_gotoend(t_cmdlst *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
