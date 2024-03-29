/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:03:02 by jcoquard          #+#    #+#             */
/*   Updated: 2024/03/27 18:29:55 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_cam(t_data *sl, t_entity *pl)
{
	if (sl->map.w * 128 > sl->win.w)
	{
		if (pl->pos.x >= sl->win.w * 0.5)
			sl->map.pos.x = -(pl->pos.x - (sl->win.w * 0.5));
		if (sl->map.pos.x * -1 > (sl->map.w * 128) - sl->win.w)
			sl->map.pos.x = (sl->map.w * -128) + sl->win.w;
	}
	if (sl->map.h * 128 > sl->win.h)
	{
		if (pl->pos.y >= sl->win.h * 0.5)
			sl->map.pos.y = -(pl->pos.y - (sl->win.h * 0.5));
		if (sl->map.pos.y * -1 > (sl->map.h * 128) - sl->win.h)
			sl->map.pos.y = (sl->map.h * -128) + sl->win.h;
	}
}

static void	init_pl(t_entity *e, int x, int y)
{
	e->id = 0;
	e->type = PLAYER;
	e->active = 1;
	e->pos.x = x * 128;
	e->pos.y = y * 128;
	e->tpos.x = 40;
	e->tpos.y = 32;
	e->w = 48;
	e->h = 92;
	e->delay = 150;
}

static void	init_bad(t_entity *e, int x, int y)
{
	e->id = 0;
	e->type = BAD;
	e->active = 0;
	e->pos.x = x * 128;
	e->pos.y = y * 128;
	e->tpos.x = 32;
	e->tpos.y = 32;
	e->w = 64;
	e->h = 92;
}

static void	init_dog(t_entity *e, int x, int y, int nb)
{
	e->id = nb;
	e->type = DOG;
	e->active = 1;
	e->pos.x = x * 128;
	e->pos.y = y * 128;
	e->tpos.x = 32;
	e->tpos.y = 32;
	e->w = 64;
	e->h = 92;
	e->delay = 50;
}

void	init_entity(t_data *sl, char tile, int x, int y)
{
	if (tile == 'P')
	{
		ft_setvec(&sl->map.start, x, y);
		init_pl(&sl->pl, x, y);
		init_cam(sl, &sl->pl);
		set_tile(&sl->map, x, y, '0');
	}
	if (tile == 'E')
	{
		ft_setvec(&sl->map.end, x, y);
		init_bad(&sl->bad, x, y);
	}
	if (tile == 'C')
		init_dog(&sl->dogs[sl->nb_dogs - 1], x, y, sl->nb_dogs);
}
