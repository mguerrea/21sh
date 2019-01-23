/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:46:04 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/23 14:04:02 by mguerrea         ###   ########.fr       */
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
# include <stdio.h>

# define NB_BUILTIN 6

typedef enum		e_pipemask
{
	PIPE_R = 1 << 0,
	PIPE_L = 1 << 1
}				t_pipemask;

typedef enum		e_redirtype
{
	STDIN_SPL,
	STDIN_DBL,
	STDOUT_SPL,
	STDOUT_DBL
}					t_redirtype;

typedef struct		s_redir
{
	char			*file;
	t_redirtype		type;
}					t_redir;

typedef struct		s_cmdlst
{
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
void	format_args(char ***args, char **environ);
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
int	do_pipe(t_cmdlst *cmd);

#endif
