/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:41:55 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/20 15:59:33 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*cut_line(const char *s, size_t len)
{
	char	*tkn_txt;
	t_token	*tkn;

	tkn_txt = NULL;
	tkn = NULL;
	if (!(tkn_txt = ft_strsub(s, 0, len)))
		return (NULL);
	tkn = tkn_create(tkn_txt);
	free(tkn_txt);
	return (tkn);
}

static void	state_standard(t_lexer *lxr)
{
	if (ft_isspace(*lxr->current))
		return ;
	if (isoperator_start(*lxr->current))
	{
		lxr->state = STATE_OPERATOR;
	}
	else if (ft_isdigit(*lxr->current))
	{
		lxr->state = STATE_IO_NUMBER;
	}
	else
	{
		if (*lxr->current == SGL_QUOTE || *lxr->current == DBL_QUOTE)
			lxr->quoting = *lxr->current;
		lxr->state = STATE_WORD;
	}
	lxr->tkn_start = lxr->current;
}

static void	state_word(t_lexer *lxr, t_token **tknlst)
{
	t_token	*tkn;

	if (lxr->quoting)
	{
		if (*lxr->current == lxr->quoting)
			lxr->quoting = 0;
	}
	else if (*lxr->current == SGL_QUOTE || *lxr->current == DBL_QUOTE)
		lxr->quoting = *lxr->current;
	else if (ft_isspace(*lxr->current) || isoperator_start(*lxr->current))
	{
		if (!(tkn = cut_line(lxr->tkn_start, lxr->current - lxr->tkn_start)))
			malloc_error();
		tkn->type = WORD;
		tkn_lst_append(tknlst, tkn);
		if (ft_isspace(*lxr->current))
			lxr->state = STATE_STD;
		else if (isoperator_start(*lxr->current))
		{
			lxr->state = STATE_OPERATOR;
			lxr->tkn_start = lxr->current;
		}
	}
}

static void	finalize_lexing(t_lexer *lxr, t_token **tknlst)
{
	t_token		*tkn;

	if (lxr->state != STATE_STD)
	{
		if (!(tkn = cut_line(lxr->tkn_start, lxr->current - lxr->tkn_start)))
			malloc_error();
		if (lxr->state == STATE_WORD || lxr->state == STATE_IO_NUMBER)
			tkn->type = WORD;
		else if (lxr->state == STATE_OPERATOR)
			set_operator_type(tkn);
		tkn_lst_append(tknlst, tkn);
	}
}

t_token		*tokenize_line(const char *line)
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
		else if (lxr.state == STATE_IO_NUMBER)
			state_ionumber(&lxr, &tknlst);
		++lxr.current;
	}
	finalize_lexing(&lxr, &tknlst);
	return (tknlst);
}
