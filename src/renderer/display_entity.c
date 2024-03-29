/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_entity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:15:17 by jcoquard          #+#    #+#             */
/*   Updated: 2024/03/25 01:11:56 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_hitbox(t_data *sl, t_entity *e)
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

t_img	*wich_texture(t_data *sl, t_entity *e)
{
	if (e->type == PLAYER)
		return (&(sl->tex_pl[e->dir][e->animation]));
	if (e->type == DOG)
		return (&(sl->tex_dog[e->dir][e->animation]));
	else
		return (&(sl->tex_wolf[e->dir][e->animation]));
}

void	draw_entity(t_data *sl, t_entity *e)
{
	int	x;
	int	y;
	int	x_e;
	int y_e;

	x_e = e->pos.x + sl->map.pos.x;
	x = -1;
	while (x++ < wich_texture(sl, e)->img_w -1)
	{
		y = -1;
		y_e = e->pos.y + sl->map.pos.y;
		while (x_e > 0 && x_e < sl->win.w && y++ < wich_texture(sl, e)->img_h - 1)
		{
			if (get_pixel(wich_texture(sl, e), x, y) >> 24 == 0 && x_e > 0 && x_e < sl->win.w && y_e > 0 && y_e < sl->win.h)
				put_pixel(&(sl->win.renderer),x_e, y_e, transparence(get_pixel(wich_texture(sl, e), x, y), sl->col_sky, sl->night));
			y_e++;
		}
		x_e++;
	}
	if (sl->keys.show_hitbox)
		display_hitbox(sl, e);
}

int	find_index(t_entity **entities, int start, int end, int min)
{
	if (start > end)
		return (min);
	if (entities[start]->pos.y < entities[min]->pos.y)
		return (find_index(entities, start + 1, end, start));
	else
		return (find_index(entities, start + 1, end, min));
}

void	display_entity(t_data *sl, t_entity **mobs, int start, int end)
{
	int			min;
	t_entity	*tmp;

	if (start > end)
		return ;
	min = find_index(mobs, start, end, start);
	tmp = mobs[start];
	mobs[start] = mobs[min];
	mobs[min] = tmp;
	if (mobs[start]->type != BAD || sl->is_night)
		draw_entity(sl, mobs[start]);
	display_entity(sl, mobs, start + 1, end);
}
