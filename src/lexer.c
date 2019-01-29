/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:41:55 by gmichaud          #+#    #+#             */
/*   Updated: 2019/01/29 18:26:41 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parser.h"

int		isoperator(const char *beg, const char *end)
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

int		isoperator_start(char c)
{
	static const char	*operators_beg = "><|;";
	
	return (ft_strchr(operators_beg, c) != NULL);
}

void	state_operator(t_lexer *lxr, t_token **tknlst)
{
	char	*tkn_txt;

	if (isoperator(lxr->tkn_start, lxr->current))
		return ;
	tkn_txt = ft_strsub(lxr->tkn_start, 0, lxr->current - lxr->tkn_start);
	tkn_lst_push(tknlst, tkn_create(tkn_txt));
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

// void	state_ionumber(t_lexer *lxr, t_token **tknlst)
// {
// 	char	*tkn_txt;

// 	if (ft_isdigit(*lxr->current))
// 		return ;
// }

void	state_standard(t_lexer *lxr)
{
	if (ft_isspace(*lxr->current))
		return ;
	if (isoperator_start(*lxr->current))
		lxr->state = STATE_OPERATOR;
	else
	{
		if (*lxr->current == SGL_QUOTE || *lxr->current == DBL_QUOTE)
			lxr->quoting = *lxr->current;
		lxr->state = STATE_WORD;
	}
	lxr->tkn_start = lxr->current;
}

void	state_word(t_lexer *lxr, t_token **tknlst)
{
	char	*tkn_txt;

	if (lxr->quoting)
	{
		if (*lxr->current == lxr->quoting)
			lxr->quoting = 0;
		return ;
	}
	if (ft_isspace(*lxr->current))
	{
		tkn_txt = ft_strsub(lxr->tkn_start, 0, lxr->current - lxr->tkn_start);
		tkn_lst_push(tknlst, tkn_create(tkn_txt));
		lxr->state = STATE_STD;
	}
	else if (isoperator_start(*lxr->current))
	{
		tkn_txt = ft_strsub(lxr->tkn_start, 0, lxr->current - lxr->tkn_start);
		tkn_lst_push(tknlst, tkn_create(tkn_txt));
		lxr->state = STATE_OPERATOR;
		lxr->tkn_start = lxr->current;
	}
	else if (*lxr->current == SGL_QUOTE || *lxr->current == DBL_QUOTE)
		lxr->quoting = *lxr->current;
}

t_token	*tokenize_line(const char *line)
{
	t_lexer		lxr;
	t_token		*tknlst;

	lxr.quoting = 0;
	lxr.state = STATE_STD;
	lxr.current = line;
	lxr.tkn_start = line;
	tknlst = NULL;
	while (*lxr.current)
	{
		if (lxr.state == STATE_STD)
			state_standard(&lxr);
		else if (lxr.state == STATE_WORD)
			state_word(&lxr, &tknlst);
		else if (lxr.state == STATE_OPERATOR)
			state_operator(&lxr, &tknlst);
		++lxr.current;
	}
	if (lxr.state == STATE_WORD)
	{
		tkn_lst_push(&tknlst, tkn_create(
			ft_strsub(lxr.tkn_start, 0, lxr.current - lxr.tkn_start)));
	}
	return (tknlst);
}
