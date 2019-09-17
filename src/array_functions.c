/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 17:58:37 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/12 14:58:31 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tabdup(char **dest, char **src)
{
	int i;

	i = 0;
	while (src[i])
		i++;
	if (!(dest = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		if (!(dest[i] = ft_strdup(src[i])))
			return (NULL);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_addentry(char **array, int size, char *str)
{
	char	**newarray;
	int		i;

	i = 0;
	if (!(newarray = (char **)malloc(sizeof(char *) * (size + 2))))
		return (NULL);
	while (array[i])
	{
		if (!(newarray[i] = ft_strdup(array[i])))
			return (NULL);
		i++;
	}
	if (!(newarray[i] = ft_strdup(str)))
		return (NULL);
	newarray[i + 1] = NULL;
	if (array)
		free_tab(array);
	return (newarray);
}

void	ft_delentry(char ***array, int pos)
{
	ft_strdel(&((*array)[pos]));
	while ((*array)[pos + 1])
	{
		(*array)[pos] = ft_strdup((*array)[pos + 1]);
		ft_strdel(&((*array)[pos + 1]));
		pos++;
	}
	if ((*array)[pos])
		ft_strdel(&((*array)[pos]));
}

char	*ft_strjointab(char **array, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (array[i])
		len += ft_strlen(array[i++]);
	if (!(str = ft_strnew(len + i - 1)))
		return (NULL);
	i = 0;
	while (array[i])
	{
		ft_strcat(str, array[i]);
		if (array[i + 1])
			str[ft_strlen(str)] = c;
		i++;
	}
	return (str);
}
