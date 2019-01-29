/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:28:17 by gmichaud          #+#    #+#             */
/*   Updated: 2019/01/27 17:47:36 by gmichaud         ###   ########.fr       */
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
