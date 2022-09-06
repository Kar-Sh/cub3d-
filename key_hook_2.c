/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <kshegunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:17:28 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 22:32:04 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_press(t_info *m)
{
	m->left = 0;
	m->right = 0;
	m->up = 0;
	m->down = 0;
}

int	key_pressed(int keycode, t_info *m)
{
	if (keycode == MLX_UP_1 || keycode == MLX_UP_2)
		m->up = 1;
	else if (keycode == MLX_DOWN_1 || keycode == MLX_DOWN_2)
		m->down = 1;
	else if (keycode == MLX_LEFT_1 || keycode == MLX_LEFT_2)
		m->left = 1;
	else if (keycode == MLX_RIGHT_1 || keycode == MLX_RIGHT_2)
		m->right = 1;
	else if (keycode == MLX_ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

int	key_released(int keycode, t_info *m)
{
	if (keycode == MLX_UP_1 || keycode == MLX_UP_2)
		m->up = 0;
	else if (keycode == MLX_DOWN_1 || keycode == MLX_DOWN_2)
		m->down = 0;
	else if (keycode == MLX_LEFT_1 || keycode == MLX_LEFT_2)
		m->left = 0;
	else if (keycode == MLX_RIGHT_1 || keycode == MLX_RIGHT_2)
		m->right = 0;
	return (0);
}

int	win_destroy(void)
{
	exit(EXIT_SUCCESS);
}
