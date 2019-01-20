/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:28:34 by mguerrea          #+#    #+#             */
/*   Updated: 2019/01/04 12:28:13 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(char *str, char *perm)
{
	if (perm && ft_strchr(perm, '\n'))
		return (ft_strjoin(ft_strchr(perm, '\n') + 1, str));
	if (ft_strchr(str, '\n'))
	{
		free(perm);
		return (ft_strdup(ft_strchr(str, '\n') + 1));
	}
	return (ft_strnew(0));
}

char	*ft_cpy_line(char *dst, char *src, char **perm)
{
	size_t i;
	size_t len;

	i = 0;
	if (*perm && ft_strchr(*perm, '\n'))
	{
		while ((*perm)[i] != '\n')
			i++;
		dst = ft_strncpy(ft_strnew(i), *perm, i);
		*perm = ft_save(src, *perm);
		return (dst);
	}
	while (src[i] != '\n' && src[i])
		i++;
	len = (*perm) ? i + ft_strlen(*perm) : i;
	dst = ft_strnew(len);
	if (*perm)
		dst = ft_strcpy(dst, *perm);
	dst = ft_strncat(dst, src, i);
	*perm = ft_save(src, *perm);
	free(src);
	return (dst);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	t_list		*list;
	static char	*perm[MAX_FD];

	if (!line)
		return (ERROR);
	list = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (ERROR);
		buf[ret] = '\0';
		ft_lstaddback(&list, ft_lstnew(buf, ret + 1));
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (!list && !perm[fd][0])
		return (END);
	*line = ft_cpy_line(*line, ft_list_to_str(list), &perm[fd]);
	ft_lstdel(&list, ft_elemdel);
	return (READ);
}
