/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:21:38 by gmichaud          #+#    #+#             */
/*   Updated: 2019/01/28 21:21:27 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdio.h>
# include "libft.h"

# define TKN_END 1

# define SGL_QUOTE 39
# define DBL_QUOTE 34

typedef enum		e_lxr_state
{
	STATE_STD,
	STATE_OPERATOR,
	STATE_WORD,
	STATE_IO_NUMBER
}					t_lxr_state;

typedef enum		e_tkn_type
{
	TOKEN,
	WORD
}					t_tkn_type;

typedef struct		e_token
{
	char			*word;
	t_tkn_type		type;
	struct e_token	*next;
}					t_token;

typedef struct		e_lexer
{
	const char		*tkn_start;
	const char		*current;
	char			quoting;
	t_lxr_state		state;
}					t_lexer;

t_token				*tkn_create(char *word);
void				tkn_lst_push(t_token **lst, t_token *tkn);
void				tkn_lst_delfirst(t_token **lst);
t_token				*tokenize_line(const char *line);

/*
WORD
ASSIGNMENT_WORD
NAME
NEWLINE
IO_NUMBER n[> < >> <<]
*/

#endif
