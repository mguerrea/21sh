/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:37:29 by mguerrea          #+#    #+#             */
/*   Updated: 2019/04/10 14:45:12 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_term *init_term(t_term *term)
{
	int ret;
	char *term_type;

	if ((term_type = getenv("TERM")) == NULL)
		return (NULL);
	if ((ret = tgetent(NULL, term_type)) == -1)
		return (NULL);
	if (!(term = (t_term *)malloc(sizeof(t_term))))
		return (NULL);
	if (tcgetattr(0, &term->init) == -1)
		return (NULL);
	if (tcgetattr(0, &term->cur) == -1)
		return (NULL);
	term->cur.c_lflag &= ~ICANON;
	term->cur.c_lflag &= ~ECHO;
	term->cur.c_cc[VMIN] = 1;
	term->cur.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term->cur) == -1)
		return (NULL);
	return (term);
}