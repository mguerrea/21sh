/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:09:56 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 15:58:12 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	int		len;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(str = ft_strnew(len)))
		return (NULL);
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	str = ft_strcat(str, s3);
	return (str);
}

int		ft_print(int c)
{
	ft_putchar(c);
	return (1);
}

void	ft_replace(char **str, char find, char replace)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == find)
			(*str)[i] = replace;
		i++;
	}
}
