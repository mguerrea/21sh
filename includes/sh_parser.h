/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:21:38 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/20 16:28:54 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <unistd.h>

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
	int				close;
}					t_redir;

typedef struct		s_cmdlst
{
	t_token			*argslst;
	char			**args;
	int				fd[2];
	t_pipemask		pipes;
	t_redir			redir[2];
	int				exec;
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
void				tkn_lst_del(t_token **lst);
int					io_redirect(t_token **tkn, t_cmdlst *cmd);
int					heredoc(t_token **tkn, t_redir *redir);

/*
** Lexer
*/

int					isoperator(const char *beg, const char *end);
int					isoperator_start(char c);
void				set_operator_type(t_token *tkn);
void				state_operator(t_lexer *lxr, t_token **tknlst);
void				state_ionumber(t_lexer *lxr, t_token **tknlst);
t_token				*cut_line(const char *s, size_t len);

/*
** Command list
*/

void				free_cmdlst(t_cmdlst **lst);
t_cmdlst			*cmd_create(void);
void				cmd_lst_push(t_cmdlst **lst, t_cmdlst *cmd);
void				cmd_lst_append(t_cmdlst **lst, t_cmdlst *cmd);
t_cmdlst			*cmd_lst_gotoend(t_cmdlst *lst);
void				free_cmd(t_cmdlst **cmd);

#endif
