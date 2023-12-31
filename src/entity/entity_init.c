/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:03:02 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/07 02:21:37 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	init_cam(t_data *sl, t_entity *pl)
{
	if (sl->map.w * 128 > sl->win.w)
	{
		if (pl->pos.x >= sl->win.w / 2)
			sl->map.pos.x = -128 * (((pl->pos.x - (sl->win.w / 2)) / 128));
		if (sl->map.pos.x * -1 > (sl->map.w * 128) - sl->win.w)
			sl->map.pos.x = (sl->map.w * -128) + sl->win.w;
	}
	if (sl->map.h * 128 > sl->win.h)
	{
		if (pl->pos.y >= sl->win.h / 2)
			sl->map.pos.y = -128 * (((pl->pos.y - (sl->win.h / 2)) / 128));
		if (sl->map.pos.y * -1 > (sl->map.h * 128) - sl->win.h)
			sl->map.pos.y = (sl->map.h * -128) + sl->win.h;
	}
}

static void	init_pl(t_entity *e, int x, int y)
{
	e->id = 0;
	e->type = PLAYER;
	e->alive = 1;
	e->pos.x = x * 128;
	e->pos.y = y * 128;
	e->tpos.x = 40;
	e->tpos.y = 32;
	e->w = 48;
	e->h = 92;
	e->dir = 0;
	e->nb_mv = 0;
	e->dist = 0;
	e->delay = 150;
	e->inmove = 0;
	e->animation = 0;
}

static void	init_dog(t_data *sl, int x, int y)
{
	int	i;

	i = 2;
	sl->nb_dogs = 2;
	while (i < NB_DOG + 2)
	{
		sl->entities[i].id = i - 2;
		sl->entities[i].type = DOG;
		if (i < sl->nb_dogs + 2)
			sl->entities[i].alive = 1;
		sl->entities[i].pos.x = x * 128;
		sl->entities[i].pos.y = y * 128;
		sl->entities[i].tpos.x = 32;
		sl->entities[i].tpos.y = 32;
		sl->entities[i].w = 64;
		sl->entities[i].h = 92;
		sl->entities[i].dir = 0;
		sl->entities[i].nb_mv = 0;
		sl->entities[i].dist = 0;
		sl->entities[i].inmove = 0;
		sl->entities[i].animation = 0;
		i++;
	}
}

static void	init_wolf(t_entity *e, int x, int y)
{
	e->id = 0;
	e->type = WOLF;
	e->alive = 0;
	e->pos.x = x * 128;
	e->pos.y = y * 128;
	e->tpos.x = 32;
	e->tpos.y = 32;
	e->w = 64;
	e->h = 92;
	e->dir = 0;
	e->nb_mv = 0;
	e->dist = 0;
	e->delay = 0;
	e->inmove = 0;
	e->animation = 0;
}

void	init_pos(t_data *sl)
{
	int	x;
	int	y;

	x = -1;
	while (++x < sl->map.w)
	{
		y = -1;
		while (++y < sl->map.h)
		{
			if (get_tile(sl, x, y) == 'P')
			{
				init_pl(&(sl->entities[0]), x, y);
				init_cam(sl, &(sl->entities[0]));
			}
			if (get_tile(sl, x, y) == 'S')
			{
				init_wolf(&(sl->entities[1]), x, y);
				init_dog(sl, x, y);
			}
			if (get_tile(sl, x, y) == 'E')
			{
				sl->map.end.x = x * 128;
				sl->map.end.y = y * 128;
			}
		}
	}
}