/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:45:37 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/05 19:09:57 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void	init_vector(char dir, double *x, double *y)
{
	if (dir == START_N)
	{
		*x = 0;
		*y = -1;
	}
	else if (dir == START_S)
	{
		*x = 0;
		*y = 1;
	}
	else if (dir == START_E)
	{
		*x = 1;
		*y = 0;
	}
	else if (dir == START_W)
	{
		*x = -1;
		*y = 0;
	}
}

static void	init_starting_position(t_info *m, int i, int j)
{
	m->x_cur = j + 0.5;
	m->y_cur = i + 0.5;
	init_vector(m->m[i][j], &m->x_dir, &m->y_dir);
	if (m->m[i][j] == START_N)
		init_vector(START_E, &m->x_plane, &m->y_plane);
	else if (m->m[i][j] == START_S)
		init_vector(START_W, &m->x_plane, &m->y_plane);
	else if (m->m[i][j] == START_E)
		init_vector(START_S, &m->x_plane, &m->y_plane);
	else if (m->m[i][j] == START_W)
		init_vector(START_N, &m->x_plane, &m->y_plane);
}

/*
 * checks that we have not encountered any starting point twice
 */
static	int	validate_start(t_info *m, int *flag, int i, int j)
{
	if (m->m[i][j] == START_N || m->m[i][j] == START_S ||
		m->m[i][j] == START_E || m->m[i][j] == START_W)
	{
		if (*flag)
			return (0);
		init_starting_position(m, i, j);
		*flag = 1;
	}
	return (1);
}

static int	validate_current(t_info *m, int i, int j, int *flag)
{
	if (i != 0 && j != 0 && m->m[i + 1] && m->m[i][j + 1] &&
		(int)ft_strlen(m->m[i - 1]) > j && (int)ft_strlen(m->m[i + 1]) > j &&
		partofmap(m->m[i - 1][j]) && partofmap(m->m[i][j + 1]) &&
		partofmap(m->m[i + 1][j]) && partofmap(m->m[i][j - 1]) &&
			validate_start(m, flag, i, j))
		return (1);
	return (0);
}
/*
 *
 * iterate over all chars in the map and check that
 * - every char is either a space or a map char
 * - every non-wall char is surrounded by any of the allowed map chars (wall
 *   or non-wall char)
 * 
 * more precisely, every non-wall character
 * - should not be in the first or last row or column
 * - the previous/next row has to have a char right above/below the current one
 * - neighbors above, to the right, below and to the left have to be map chars
 */

int	validate_input(t_info	*m)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (m->m[i])
	{
		j = 0;
		while (m->m[i][j])
		{
			if (m->m[i][j] != ' ' && !partofmap(m->m[i][j]))
				return (0);
			if (nonwall_partofmap(m->m[i][j]))
			{
				if (!validate_current(m, i, j, &flag))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
