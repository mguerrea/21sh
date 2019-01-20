/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:46:04 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/08 13:09:56 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/param.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>

# define NB_BUILTIN 6

typedef int	(*t_built_in)(char **, char ***);

void	print_prompt(char **environ);
int		ft_cd(char **args, char ***environ);
int		ft_exit(char **args, char ***environ);
int		ft_echo(char **args, char ***environ);
int		ft_env(char **args, char ***environ);
void	ft_setvar(char ***environ, char *var, char *value);
int		ft_setenv(char **args, char ***environ);
char	**ft_tabdup(char **dest, char **src);
char	**ft_getenv(char **environ, char *var);
char	**ft_addentry(char **tab, int size, char *str);
void	ft_delentry(char ***tab, int pos);
int		ft_unsetenv(char **args, char ***environ);
int		launch_bin(char **args, char ***envriton);
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

#endif
