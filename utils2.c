/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 02:19:11 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 02:19:13 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	partofmap(char c)
{
	if (c == EMP_SPC || c == WALL || c == START_N
		|| c == START_S || c == START_E || c == START_W)
		return (1);
	return (0);
}

int	nonwall_partofmap(char c)
{
	if (c == EMP_SPC || c == START_N
		|| c == START_S || c == START_E || c == START_W)
		return (1);
	return (0);
}
