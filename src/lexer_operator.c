/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:01:44 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/10 16:34:29 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_operator_type(t_token *tkn)
{
	if (!strcmp(tkn->word, ">"))
		tkn->type = GREAT;
	else if (!strcmp(tkn->word, ">>"))
		tkn->type = DGREAT;
	else if (!strcmp(tkn->word, "<"))
		tkn->type = LESS;
	else if (!strcmp(tkn->word, "<<"))
		tkn->type = DLESS;
	else if (!strcmp(tkn->word, ">&"))
		tkn->type = GREATAND;
	else if (!strcmp(tkn->word, "<&"))
		tkn->type = LESSAND;
	else if (!strcmp(tkn->word, "|"))
		tkn->type = PIPE;
	else if (!strcmp(tkn->word, ";"))
		tkn->type = SEMI;
}

int			isoperator_start(char c)
{
	static const char	*operators_beg = "><|;";

	return (ft_strchr(operators_beg, c) != NULL);
}

int			isoperator(const char *beg, const char *end)
{
	static const char	comp_operators[4][2] = {">>", "<<", ">&", "<&"};
	size_t				i;

	i = 0;
	while (i < 4)
	{
		if (!strncmp(beg, comp_operators[i], end - beg + 1))
			return (1);
		++i;
	}
	return (0);
}

void		state_operator(t_lexer *lxr, t_token **tknlst)
{
	t_token	*tkn;

	if (isoperator(lxr->tkn_start, lxr->current))
		return ;
	if (!(tkn = cut_line(lxr->tkn_start, lxr->current - lxr->tkn_start)))
		malloc_error();
	set_operator_type(tkn);
	tkn_lst_append(tknlst, tkn);
	if (ft_isspace(*lxr->current))
		lxr->state = STATE_STD;
	else
	{
		if (isoperator_start(*lxr->current))
			lxr->state = STATE_OPERATOR;
		else
			lxr->state = STATE_WORD;
		lxr->tkn_start = lxr->current;
		if (*lxr->current == SGL_QUOTE || *lxr->current == DBL_QUOTE)
			lxr->quoting = *lxr->current;
	}
}

void		state_ionumber(t_lexer *lxr, t_token **tknlst)
{
	t_token	*tkn;

	if (ft_isdigit(*lxr->current))
		return ;
	if (*lxr->current == '>' || *lxr->current == '<')
	{
		if (!(tkn = cut_line(lxr->tkn_start, lxr->current - lxr->tkn_start)))
			malloc_error();
		tkn->type = IO_NUMBER;
		tkn_lst_append(tknlst, tkn);
		lxr->state = STATE_OPERATOR;
		lxr->tkn_start = lxr->current;
	}
	else
	{
		lxr->state = STATE_WORD;
	}
}
