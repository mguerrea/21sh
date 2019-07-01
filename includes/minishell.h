/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:46:04 by mguerrea          #+#    #+#             */
/*   Updated: 2019/07/01 14:53:13 by mguerrea         ###   ########.fr       */
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
# include <stdio.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <signal.h>

# define NB_BUILTIN 6

typedef struct		s_term
{
	struct termios	init;
	struct termios	cur;
}					t_term;

typedef struct 		s_history
{
	char				*line;
	struct s_history	*prev;
	struct s_history	*next;
}					t_history;

typedef int	(*t_built_in)(t_cmdlst *, char ***);

t_term *g_term;
pid_t g_pid;

/*
** RUN
*/

int		ft_exit(t_cmdlst *cmd, char ***environ);
int		ft_echo(t_cmdlst *cmd, char ***environ);
int		ft_env(t_cmdlst *cmd, char ***environ);
int		ft_cd(t_cmdlst *cmd, char ***environ);
int		launch_bin(t_cmdlst *cmd, char ***envriton);

/*
** PROMPT
*/

void	print_prompt(void);
int		wrong_quote(char *str);

/*
** ENVIRON
*/

void	ft_setvar(char ***environ, char *var, char *value);
int		ft_setenv(t_cmdlst *cmd, char ***environ);
char	**ft_getenv(char **environ, char *var);
int		ft_unsetenv(t_cmdlst *cmd, char ***environ);

/*
** ARRAY_FUNCTIONS
*/

char	**ft_tabdup(char **dest, char **src);
char	**ft_addentry(char **array, int size, char *str);
void	ft_delentry(char ***array, int pos);
void	free_tab(char **array);
char	*ft_strjointab(char **array, char c);

/*
** HISTORY
*/

int		save_history(t_history **history, char **line);
void 		manage_history(char *buff, t_history **history, char *line, int *pos);
t_history 	*add_to_history(t_history **history);
void		free_history(t_history **history);

/*
** ERRORS
*/

void	error_file(char *cmd, char *errors);
void	malloc_error(void);
void	error_rights(char *cmd, char *str);
void	error_cmd(char *str);
int		error_args(char *cmd);
int		throw_error(char *str);
void	error_fd(int fd);

/*
** INIT
*/

char	**init_shell(char **environ);
t_term		*init_term(t_term *term);

/*
** BASICS
*/

char	*ft_strjoin3(char *s1, char *s2, char *s3);
int		ft_print(int c);

/*
** COMMAND LINE
*/

void ft_insert(char *line, char c, int pos);
void ft_delete(char *line, int pos);
int	get_line(t_history **history);

/*
** I/O
*/

int		do_pipe(t_cmdlst *cmd);
int		redirection(t_cmdlst *cmd);

/*
** CURSOR
*/

void	move_right(int *pos);
void	move_left(int *pos);

void handle_parent(int sig);
void catch_signals(int parent);

#endif
