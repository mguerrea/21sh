/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:28:17 by gmichaud          #+#    #+#             */
/*   Updated: 2019/04/13 14:37:30 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parser.h"

t_token	*tkn_create(char *word)
{
	t_token	*token;

	if (!(token = (t_token*)malloc(sizeof(t_token))))
		return NULL;
	token->word = word;
	token->type = TOKEN;
	token->next = NULL;
	return (token);
}

void	tkn_lst_push(t_token **lst, t_token *tkn)
{
	if (lst)
	{
		tkn->next = *lst;
		*lst = tkn;
	}
}

void tkn_lst_append(t_token **lst, t_token *tkn)
{
	t_token *tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = tkn;
	}
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tkn;
	}
}

void	tkn_lst_delfirst(t_token **lst)
{
	t_token	*tmp;

	if (lst && *lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}
