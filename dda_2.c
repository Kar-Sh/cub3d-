/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshegunt <kshegunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:18:54 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 22:16:20 by kshegunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	create_trgb(unsigned char t, \
unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

void	ceil_c(t_info *m, int drawstart, int x)
{
	while (m->i < drawstart)
	{
		m->dst = m->cur_img.img_addr + m->i * m->cur_img.size_line + \
		x * (m->cur_img.bits_per_pixel / 8);
		*(unsigned int *)m->dst = create_trgb(0, m->ceil_c[0], \
		m->ceil_c[1], m->ceil_c[2]);
		m->i++;
	}
}

void	floor_c(t_info *m, int x)
{
	while (m->i < WIN_HEIGHT)
	{
		m->dst = m->cur_img.img_addr + (m->i * m->cur_img.size_line + \
		x * (m->cur_img.bits_per_pixel / 8));
		*(unsigned int *)m->dst = create_trgb(0, m->floor_c[0], \
		m->floor_c[1], m->floor_c[2]);
		m->i++;
	}	
}

void	vert_line(int x, int drawstart, int drawend, t_info	*m)
{
	int		texx;
	char	*color_addr;
	int		texy;

	texx = (int)(m->wallx * (double)(m->cur_t->size_line)) / 4 * 4;
	if ((m->side == 0 && m->raydirx > 0) || (m->side == 1 && m->raydiry < 0))
		texx = (m->cur_t->size_line - texx - 1) / 4 * 4;
	m->i = 0;
	ceil_c(m, drawstart, x);
	while (m->i < drawend)
	{
		texy = (int)m->texpos & (m->cur_t->h - 1);
		m->texpos += m->texstep;
		color_addr = &m->cur_t->\
		img_addr[m->cur_t->size_line * texy + texx];
		m->dst = m->cur_img.img_addr + (m->i * m->cur_img.size_line + \
		x * (m->cur_img.bits_per_pixel / 8));
		*(unsigned int *)m->dst = create_trgb(*(color_addr + 3), \
		*(color_addr + 2), *(color_addr + 1), *color_addr);
		m->i++;
	}
	floor_c(m, x);
}

void	drawline(double perpwalldist, int x, t_info *m)
{
	int	lineheight;
	int	drawstart;
	int	drawend;
	int	h;

	h = WIN_HEIGHT;
	lineheight = (int)(h / perpwalldist);
	drawstart = -lineheight / 2 + h / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + h / 2;
	if (drawend >= h)
		drawend = h - 1;
	m->texstep = 1.0 * m->cur_t->h / lineheight;
	m->texpos = (drawstart - h / 2 + lineheight / 2) * m->texstep;
	vert_line(x, drawstart, drawend, m);
}
