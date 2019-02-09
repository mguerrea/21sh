/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:46:04 by mguerrea          #+#    #+#             */
/*   Updated: 2019/02/09 19:00:27 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include "libft.h"
# include "get_next_line.h"
# include "sh_parser.h"

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
	SEMI
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

# define NB_BUILTIN 6

typedef enum		e_pipemask
{
	PIPE_R = 1 << 0,
	PIPE_L = 1 << 1
}				t_pipemask;

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

typedef int	(*t_built_in)(t_cmdlst *, char ***);

void	print_prompt(char **environ);
int		ft_cd(t_cmdlst *cmd, char ***environ);
int		ft_exit(t_cmdlst *cmd, char ***environ);
int		ft_echo(t_cmdlst *cmd, char ***environ);
int		ft_env(t_cmdlst *cmd, char ***environ);
void	ft_setvar(char ***environ, char *var, char *value);
int		ft_setenv(t_cmdlst *cmd, char ***environ);
char	**ft_tabdup(char **dest, char **src);
char	**ft_getenv(char **environ, char *var);
char	**ft_addentry(char **tab, int size, char *str);
void	ft_delentry(char ***tab, int pos);
int		ft_unsetenv(t_cmdlst *cmd, char ***environ);
int		launch_bin(t_cmdlst *cmd, char ***envriton);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
// void	format_args(char ***args, char **environ);
void	format_args(t_cmdlst *cmd, char **environ);
void	free_tab(char **tab);
char	**split_quotes(char *line, char c);
void	error_file(char *cmd, char *errors);
char	**init_shell(char **environ, t_built_in *builin_fct);
void	fill_built(t_built_in *builtin_fct);
char	*get_cmd(char **env);
void	malloc_error(void);
void	error_rights(char *cmd, char *str);
void	error_cmd(char *str);
int		error_args(char *cmd);
char	*ft_strjointab(char **tab, char c);
t_cmdlst			*parse(t_token *tknlst);
int		do_pipe(t_cmdlst *cmd);
int		throw_error(char *str);
int redirection(t_cmdlst *cmd);
void	error_fd(int fd);

#endif
