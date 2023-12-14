/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_entity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:15:17 by jcoquard          #+#    #+#             */
/*   Updated: 2023/09/03 17:43:53 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	display_hitbox(t_data *sl, t_entity *e)
{
	int	x;
	int	y;

	x = e->tpos.x - 1;
	while (x++ < e->w + e->tpos.x)
	{
		y = e->tpos.y - 1;
		while (y++ < e->h + e->tpos.y)
		{
			if (e->pos.x + x + sl->map.pos.x > 0 && e->pos.x + x
				+ sl->map.pos.x < sl->win.w && e->pos.y + y + sl->map.pos.y
				> 0 && e->pos.y + y + sl->map.pos.y < sl->win.h && (x
					== e->tpos.x || y == e->tpos.y || x == e->w + e->tpos.x - 1
					|| y == e->h + e->tpos.y - 1))
				put_pixel(&(sl->win.renderer), e->pos.x + x + sl->map.pos.x,
					e->pos.y + y + sl->map.pos.y, 0xFFFF0000);
		}
	}
}

void	display_entity(t_data *sl, t_entity *e)
{
	int	x;
	int	y;

	x = -1;
	while (x++ < e->tex[e->dir][e->animation].img_w -1)
	{
		y = -1;
		while (y++ < e->tex[e->dir][e->animation].img_h - 1)
		{
			if (get_pixel(&(e->tex[e->dir][e->animation]), x, y) >> 24 == 0
				&& e->pos.x + x + sl->map.pos.x > 0 && e->pos.x + x
				+ sl->map.pos.x < sl->win.w && e->pos.y + y + sl->map.pos.y
				> 0 && e->pos.y + y + sl->map.pos.y < sl->win.h)
				put_pixel(&(sl->win.renderer), e->pos.x + x + sl->map.pos.x,
					e->pos.y + y + sl->map.pos.y, transparence(get_pixel(
							&(e->tex[e->dir][e->animation]), x, y),
						C_NIGHT, sl->trans));
		}
	}
	if (sl->show_hitbox)
		display_hitbox(sl, e);
}

void	display_dog(t_data *sl, t_entity *e)
{
	int	x;
	int	y;

	x = -1;
	while (x++ < sl->dog[0].tex[e->dir][e->animation].img_w -1)
	{
		y = -1;
		while (y++ < sl->dog[0].tex[e->dir][e->animation].img_h - 1)
		{
			if (get_pixel(&(sl->dog[0].tex[e->dir][e->animation]), x, y) >> 24
				== 0 && e->pos.x + x + sl->map.pos.x > 0 && e->pos.x + x
				+ sl->map.pos.x < sl->win.w && e->pos.y + y + sl->map.pos.y
				> 0 && e->pos.y + y + sl->map.pos.y < sl->win.h)
				put_pixel(&(sl->win.renderer), e->pos.x + x + sl->map.pos.x,
					e->pos.y + y + sl->map.pos.y,
					transparence(get_pixel(
							&(sl->dog[0].tex[e->dir][e->animation]), x, y),
						C_NIGHT, sl->trans));
		}
	}
	if (sl->show_hitbox)
		display_hitbox(sl, e);
}

static void	animation_entity(t_entity *e)
{
		if (e->inmove)
			e->animation = (e->animation + 1) % 4;
		else
			e->animation = 0;
}

void	animation(t_data *sl)
{
	int	i;

	i = -1;
	if (sl->time >= 7)
	{
		animation_entity(&(sl->pl));
		while (++i < sl->nb_dogs && sl->dog[i].alive)
			animation_entity(&(sl->dog[i]));
		if (sl->wolf.alive)
			animation_entity(&(sl->wolf));
		sl->time = 0;
		sl->pl.inmove = 0;
	}
	++sl->time;
}
