/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <kshegunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 02:24:25 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 22:33:05 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void	validate_filename(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 4)
		error_exit("Error\nInvalid filename\n", EXIT_FAILURE);
	if (ft_strncmp(name + len - 4, ".cub", len))
		error_exit("Error\nInvalid filename\n", EXIT_FAILURE);
}

void	process_input(int argc, char **argv, t_info *m)
{
	int		fd;
	t_list	*lines;

	if (argc == 2)
	{
		validate_filename(argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			error_exit("Error\nFailed to open the file\n", EXIT_FAILURE);
		lines = extract_input_lines(fd);
		lines = construct_elements(lines, m, 0);
		m->m = construct_map(lines);
		return ;
	}
	else
	{
		ft_putstr_fd("Usage:\n\n\tcub <some_map.cub>\n", 1);
		exit(EXIT_SUCCESS);
	}
}
