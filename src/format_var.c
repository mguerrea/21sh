/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:11:59 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/21 16:04:52 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_formated_string(char *s, char *var, char *varname,
	size_t index)
{
	char	*tmp;
	char	*ret;

	if (!(tmp = ft_strsub(s, 0, index)))
		malloc_error();
	if (!(ret = ft_strjoin3(tmp, var, s + index + ft_strlen(varname) + 1)))
		malloc_error();
	free(tmp);
	return (ret);
}

static char		*get_varname(char *s)
{
	size_t	i;
	char	*ret;

	i = 1;
	while (s[i] && s[i] != '"' && s[i] != ' ' && s[i] != '$' && s[i] != '\'')
		++i;
	if (i == 1)
		return (NULL);
	if (!(ret = ft_strsub(s, 1, i - 1)))
		malloc_error();
	return (ret);
}

static char		*get_formated_var(char **var, size_t *len)
{
	char	*dest;
	size_t	i;

	*len = 0;
	i = 0;
	while (var[i++])
	{
		*len += ft_strlen(var[i]) + 1;
	}
	if (!(dest = (char*)malloc(sizeof(char) * *len)))
		malloc_error();
	i = 0;
	while (var[i++])
	{
		ft_strcat(dest, var[i]);
		dest[ft_strlen(dest) - 1] = ':';
	}
	dest[*len] = '\0';
	return (dest);
}

static size_t	get_var(char **environ, char **s, size_t index)
{
	char	*varname;
	char	**var_env;
	char	*var;
	char	*ret;
	size_t	len;

	if (!(varname = get_varname(*s + index)))
		return (index);
	if (!(var_env = ft_getenv(environ, varname)))
	{
		ret = get_formated_string(*s, "", varname, index);
		free(varname);
		free(*s);
		*s = ret;
		return (index - 1);
	}
	var = get_formated_var(var_env, &len);
	free_tab(var_env);
	ret = get_formated_string(*s, var, varname, index);
	free(varname);
	free(*s);
	*s = ret;
	return (index + len - 1);
}

void			format_var(char **environ, char **s)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while ((*s)[i])
	{
		if (!quote)
		{
			if ((*s)[i] == '\'')
				quote = (*s)[i];
			else if ((*s)[i] == '$')
				i = get_var(environ, s, i);
		}
		else if ((*s)[i] == '\'')
		{
			quote = 0;
		}
		++i;
	}
}
