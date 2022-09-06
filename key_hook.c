/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <kshegunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:13:09 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 22:16:56 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	render_up(t_info *m)
{
	if (m->m[(int)m->y_cur][(int)(m->x_cur + m->x_dir * MOVE_SPEED)] != WALL)
		m->x_cur += m->x_dir * MOVE_SPEED;
	if (m->m[(int)(m->y_cur + m->y_dir * MOVE_SPEED)][(int)m->x_cur] != WALL)
		m -> y_cur += m->y_dir * MOVE_SPEED;
}

void	render_down(t_info *m)
{
	if (m->m[(int)m->y_cur][(int)(m->x_cur - m->x_dir * MOVE_SPEED)] != WALL)
		m->x_cur -= m->x_dir * MOVE_SPEED;
	if (m->m[(int)(m->y_cur - m->y_dir * MOVE_SPEED)][(int)m->x_cur] != WALL)
	m -> y_cur -= m->y_dir * MOVE_SPEED;
}

void	render_left(t_info *m)
{
	m->olddirx = m->x_dir;
	m->x_dir = m->x_dir * cos(-ROT_SPEED) - m->y_dir * sin(-ROT_SPEED);
	m->y_dir = m->olddirx * sin(-ROT_SPEED) + m->y_dir * cos(-ROT_SPEED);
	m->oldplanex = m->x_plane;
	m->x_plane = m->x_plane * cos(-ROT_SPEED) - m->y_plane * sin(-ROT_SPEED);
	m->y_plane = m->oldplanex * sin(-ROT_SPEED) + m->y_plane * cos(-ROT_SPEED);
}

void	render_right(t_info *m)
{
	m->olddirx = m->x_dir;
	m->x_dir = m->x_dir * cos(ROT_SPEED) - m->y_dir * sin(ROT_SPEED);
	m->y_dir = m->olddirx * sin(ROT_SPEED) + m->y_dir * cos(ROT_SPEED);
	m->oldplanex = m->x_plane;
	m->x_plane = m->x_plane * cos(ROT_SPEED) - m->y_plane * sin(ROT_SPEED);
	m->y_plane = m->oldplanex * sin(ROT_SPEED) + m->y_plane * cos(ROT_SPEED);
}

int	render_next_frame(t_info	*m)
{
	if (m->up)
		render_up(m);
	if (m->down)
		render_down(m);
	if (m->left)
		render_left(m);
	if (m->right)
		render_right(m);
	dda(m);
	return (0);
}
