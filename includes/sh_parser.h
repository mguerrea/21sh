/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:21:38 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/10 15:29:11 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

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
	WORD,
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	LESSAND,
	GREATAND,
	PIPE,
	SEMI,
	IO_NUMBER
}					t_tkn_type;

typedef struct		s_token
{
	char			*word;
	t_tkn_type		type;
	struct s_token	*next;
}					t_token;

typedef struct		s_lexer
{
	const char		*tkn_start;
	const char		*current;
	char			quoting;
	t_lxr_state		state;
}					t_lexer;

typedef enum		e_pipemask
{
	PIPE_R = 1 << 0,
	PIPE_L = 1 << 1
}					t_pipemask;

typedef enum		e_redirtype
{
	NONE,
	SPL,
	DBL
}					t_redirtype;

typedef struct		s_redir
{
	char			*file;
	int				fd[2];
	t_redirtype		type;
}					t_redir;

typedef struct		s_cmdlst
{
	t_token			*argslst;
	char			**args;
	int				fd[2];
	t_pipemask		pipes;
	t_redir			redir[2];
	struct s_cmdlst	*prev;
	struct s_cmdlst	*next;
}					t_cmdlst;

void				format_args(t_cmdlst *cmd, char **environ);
t_cmdlst			*parse(t_token *tknlst);
t_token				*tkn_create(char *word);
void				tkn_lst_push(t_token **lst, t_token *tkn);
void				tkn_lst_delfirst(t_token **lst);
t_token				*tokenize_line(const char *line);
void				tkn_lst_append(t_token **lst, t_token *tkn);

#endif
