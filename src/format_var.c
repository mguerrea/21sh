/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:11:59 by gmichaud          #+#    #+#             */
/*   Updated: 2019/09/12 11:19:44 by mguerrea         ###   ########.fr       */
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

static size_t	get_var(char **s, size_t index)
{
	char	*varname;
	char	*var;
	char	*ret;

	if (!(varname = get_varname(*s + index)))
		return (index);
	if (!(var = getenv(varname)))
	{
		ret = get_formated_string(*s, "", varname, index);
		free(varname);
		free(*s);
		*s = ret;
		return (index - 1);
	}
	ret = get_formated_string(*s, var, varname, index);
	free(varname);
	free(*s);
	*s = ret;
	return (index + ft_strlen(var) - 1);
}

void			format_var(char **s)
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
				i = get_var(s, i);
		}
		else if ((*s)[i] == '\'')
		{
			quote = 0;
		}
		++i;
	}
}
