/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <kshegunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:47:52 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 02:24:53 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	int	update_mask(int *mask, int upd)
{
	if (*mask & upd)
		error_exit("Error\nDuplicate elements in the input file\n", EXIT_FAILURE);
	*mask |= upd;
	return (1);
}

static	int	update_color(char	*s, int colors[3], int	*mask, int upd)
{
	char	**nums;
	int		i;

	nums = ft_split(s, COLOR_DELIM);
	if (ft_arrlen(nums) != RGB_CNT)
		error_exit("Error\nInvalid element (color) \
		line in the input file\n", EXIT_FAILURE);
	i = 0;
	while (nums[i])
	{
		colors[i] = ft_atoi(nums[i]);
		i++;
	}
	ft_arrfree(nums);
	free(s);
	update_mask(mask, upd);
	return (1);
}

static	int	update_element(char **split, t_info *m, int *mask)
{
	if (!ft_strncmp(split[0], NORTH_T, ft_strlen(split[0])))
	{
		m->no_t = split[1];
		return (update_mask(mask, NORTH_MASK));
	}
	else if (!ft_strncmp(split[0], SOUTH_T, ft_strlen(split[0])))
	{
		m->so_t = split[1];
		return (update_mask(mask, SOUTH_MASK));
	}
	else if (!ft_strncmp(split[0], WEST_T, ft_strlen(split[0])))
	{
		m->we_t = split[1];
		return (update_mask(mask, WEST_MASK));
	}
	else if (!ft_strncmp(split[0], EAST_T, ft_strlen(split[0])))
	{
		m->ea_t = split[1];
		return (update_mask(mask, EAST_MASK));
	}
	else if (!ft_strncmp(split[0], FLOOR_C, ft_strlen(split[0])))
		return (update_color(split[1], m->floor_c, mask, FLOOR_MASK));
	else if (!ft_strncmp(split[0], CEIL_C, ft_strlen(split[0])))
		return (update_color(split[1], m->ceil_c, mask, CEIL_MASK));
	return (0);
}

static t_list	*skip_empty_lines(t_list *lines)
{
	char	**split;
	t_list	*cur;

	split = ft_split(lines->content, ELEM_DELIM);
	while (!split || !ft_arrlen(split))
	{
		cur = lines;
		lines = cur->next;
		ft_lstdelone(cur, delete_line);
		ft_arrfree(split);
		split = ft_split(lines->content, ELEM_DELIM);
	}
	ft_arrfree(split);
	return (lines);
}

t_list	*construct_elements(t_list *lines, t_info *m, int mask)
{
	t_list	*cur;
	char	**split;

	cur = skip_empty_lines(lines);
	while (cur && (~mask & ELEM_MASK))
	{
		split = ft_split(cur->content, ELEM_DELIM);
		if (ft_arrlen(split) != 2)
			error_exit("Error\nInvalid element line in the input file\n", \
				EXIT_FAILURE);
		if (!update_element(split, m, &mask))
			error_exit("Error\nInvalid element in the input file\n", \
				EXIT_FAILURE);
		lines = cur->next;
		free(cur->content);
		free(cur);
		cur = lines;
		free(split[0]);
		free(split);
		cur = skip_empty_lines(lines);
	}
	if (!cur)
		error_exit("Error\nNo map in the input file\n", EXIT_FAILURE);
	return (cur);
}
