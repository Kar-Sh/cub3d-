/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 02:07:42 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 02:07:44 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_arrlen(char **a)
{
	int	len;

	len = 0;
	while (a[len])
		len++;
	return (len);
}

void	ft_arrfree(char **a)
{
	char	**cur;

	if (!a)
		return ;
	cur = a;
	while (*cur)
	{
		free(*cur);
		cur++;
	}
	free(a);
}

void	delete_line(void	*p)
{
	char	*line;

	line = p;
	free(line);
}

void	skip_line(void	*p)
{
	(void)p;
}

void	error_exit(char *s, int status)
{
	ft_putstr_fd(s, 2);
	exit(status);
}
