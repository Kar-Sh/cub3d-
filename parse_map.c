/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <kshegunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 02:24:42 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 02:46:35 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	t_list	*free_list(t_list **list)
{
	ft_lstclear(list, delete_line);
	return (NULL);
}

static	void	exit_if_null(void	*ptr, char	*msg)
{
	if (!ptr)
		error_exit(msg, EXIT_FAILURE);
}

int	init_textures(t_info *m)
{
	void	*img_ptr;

	img_ptr = mlx_xpm_file_to_image(m->mlx, m->no_t, &m->no.w, &m->no.h);
	exit_if_null(img_ptr, ERR_NO);
	m->no.img_addr = mlx_get_data_addr(img_ptr, &m->no.bits_per_pixel, \
	&m->no.size_line, &m->no.endian);
	exit_if_null(m->no.img_addr, ERR_NO);
	img_ptr = mlx_xpm_file_to_image(m->mlx, m->so_t, &m->so.w, &m->so.h);
	exit_if_null(img_ptr, ERR_SO);
	m->so.img_addr = mlx_get_data_addr(img_ptr, &m->so.bits_per_pixel, \
		&m->so.size_line, &m->so.endian);
	exit_if_null(m->so.img_addr, ERR_SO);
	img_ptr = mlx_xpm_file_to_image(m->mlx, m->we_t, &m->we.w, &m->we.h);
	exit_if_null(img_ptr, ERR_WE);
	m->we.img_addr = mlx_get_data_addr(img_ptr, &m->we.bits_per_pixel, \
		&m->we.size_line, &m->we.endian);
	exit_if_null(m->we.img_addr, ERR_WE);
	img_ptr = mlx_xpm_file_to_image(m->mlx, m->ea_t, &m->ea.w, &m->ea.h);
	exit_if_null(img_ptr, ERR_EA);
	m->ea.img_addr = mlx_get_data_addr(img_ptr, &m->ea.bits_per_pixel, \
		&m->ea.size_line, &m->ea.endian);
	exit_if_null(m->ea.img_addr, ERR_EA);
	return (1);
}

t_list	*extract_input_lines(int fd)
{
	char	*line;
	t_list	*cur;
	t_list	*start;
	int		ret;

	cur = NULL;
	start = NULL;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (free_list(&start));
		if (!cur)
		{
			start = ft_lstnew(line);
			cur = start;
		}
		else
		{
			ft_lstadd_back(&cur, ft_lstnew(line));
			cur = cur->next;
		}
	}
	return (start);
}

char	**construct_map(t_list *lines)
{
	int		len;
	char	**map;
	int		i;
	t_list	*cur;

	if (!lines)
		error_exit("Error\nNo map in the input file\n", EXIT_SUCCESS);
	len = ft_lstsize(lines);
	map = ft_calloc(sizeof(char *), len + 1);
	map[len] = NULL;
	i = 0;
	cur = lines;
	while (cur)
	{
		map[i] = cur->content;
		cur = cur->next;
		i++;
	}
	ft_lstclear(&lines, skip_line);
	return (map);
}
