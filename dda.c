/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <kshegunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:32:23 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 22:15:26 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	sidedist(t_info	*m)
{
	if (m->raydirx < 0)
	{
		m->stepx = -1;
		m->sidedistx = (m->x_cur - m->mapx) * m->deltadistx;
	}
	else
	{
		m->stepx = 1;
		m->sidedistx = (m->mapx + 1.0 - m->x_cur) * m->deltadistx;
	}
	if (m->raydiry < 0)
	{
		m->stepy = -1;
		m -> sidedisty = (m->y_cur - m->mapy) * m->deltadisty;
	}
	else
	{
		m->stepy = 1;
		m->sidedisty = (m->mapy + 1.0 - m->y_cur) * m->deltadisty;
	}
}

void	deltadist(t_info *m, int x, int w)
{
	m -> camerax = 2 * x / (double)w - 1;
	m -> raydirx = m -> x_dir + m -> x_plane * m ->camerax;
	m -> raydiry = m -> y_dir + m -> y_plane * m -> camerax;
	if (m -> raydirx == 0)
		m -> deltadistx = 1e30;
	else
		m -> deltadistx = fabs(sqrt(m->raydirx * m->raydirx + \
		m->raydiry * m->raydiry) / m->raydirx);
	if (m -> raydiry == 0)
		m -> deltadisty = 1e30;
	else
		m -> deltadisty = fabs(sqrt(m->raydirx * m->raydirx + \
		m->raydiry * m->raydiry) / m->raydiry);
}

void	perpwalldist(t_info	*m, int hit)
{
	while (hit == 0)
	{
		if (m->sidedistx < m->sidedisty)
		{
			m->sidedistx += m->deltadistx;
			m->mapx += m->stepx;
			m->side = 0;
		}
		else
		{
			m->sidedisty += m->deltadisty;
			m->mapy += m->stepy;
			m->side = 1;
		}
		if (m->m[m->mapy][m->mapx] == WALL)
			hit = 1;
	}
	if (m->side == 0)
		m->perpwalldist = (m->mapx - m->x_cur + \
		(1 - m->stepx) / 2) / m->raydirx;
	else
		m->perpwalldist = (m->mapy - m->y_cur + \
		(1 - m->stepy) / 2) / m->raydiry;
}

void	side(t_info *m)
{
	if (m->side == 0)
		m->wallx = m->y_cur + m->perpwalldist * m->raydiry;
	else
		m->wallx = m->x_cur + m->perpwalldist * m->raydirx;
	m->wallx -= floor(m->wallx);
	if (m->side == 0)
	{
		if (m->raydirx > 0)
			m->cur_t = &m->ea;
		else
			m->cur_t = &m->we;
	}
	else
	{
		if (m->raydiry > 0)
			m->cur_t = &m->so;
		else
			m->cur_t = &m->no;
	}
}

void	dda(t_info	*m)
{
	int	w;
	int	x;

	w = 1000;
	x = 0;
	m->cur_img.img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->cur_img.img_addr = mlx_get_data_addr(m->cur_img.img, \
	&m->cur_img.bits_per_pixel, &m->cur_img.size_line, &m->cur_img.endian);
	while (x < w)
	{
		deltadist(m, x, w);
		m->mapx = (int)m->x_cur;
		m->mapy = (int)m->y_cur;
		sidedist(m);
		perpwalldist(m, 0);
		side(m);
		drawline(m->perpwalldist, x, m);
		x++;
	}
	mlx_put_image_to_window(m->mlx, m->win, m->cur_img.img, 0, 0);
}
