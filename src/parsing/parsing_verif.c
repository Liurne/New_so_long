/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:34:36 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/07 00:44:45 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	verif_map_size(t_data *sl)
{
	int	tmp;

	tmp = 0;
	while (sl->map.map[tmp] != '\n' && sl->map.map[tmp])
		tmp++;
	if (!sl->map.map[tmp])
		return (0);
	sl->map.w = tmp;
	if ((ft_strlen(sl->map.map) + 1) % (tmp + 1))
		return (0);
	sl->map.h = (ft_strlen(sl->map.map) + 1) / (tmp + 1);
	return (1);
}

static int	parcour_map(t_data *sl)
{
	int	i;
	int	j;
	char	c;

	i = -1;
	while (++i < sl->map.w)
	{
		j = -1;
		while (++j < sl->map.h)
		{
			c = get_tile(sl, i, j);
			if (c != 'E' && c != 'C' && c != 'P' && c != '1' && c != '0'
					&& c != 'S')
				return (0);
			if (i == sl->map.w - 1 || i == 0 || j == sl->map.h - 1 || j == 0)
				if (c != '1')
					return (0);
		}
	}
	return (1);
}

static int	verif_count(t_data *sl)
{
	int	e;
	int	p;
	int	s;
	int	i;

	e = 0;
	p = 0;
	s = 0;
	i = -1;
	while (sl->map.map[++i])
	{
		if (sl->map.map[i] == 'E')
			e++;
		if (sl->map.map[i] == 'P')
			p++;
		if (sl->map.map[i] == 'S')
			s++;
		if (sl->map.map[i] == 'C')
			sl->nb_col++;
		if (sl->map.map[i] == 'C' || sl->map.map[i] == '0')
			sl->nb_case++;
	}
	if (e != 1 || p != 1 || s != 1 || sl->nb_col < 1)
		return (0);
	return (1);
}

static int	recu_finder(t_data *sl, char *map, int x, int y)
{
	if (x >= sl->map.w || x < 0 || y >= sl->map.h || y < 0
		|| map[(y * (sl->map.w + 1)) + x] == '1')
		return (0);
	map[(y * (sl->map.w + 1)) + x] = '1';
	recu_finder(sl, map, x - 1, y);
	recu_finder(sl, map, x + 1, y);
	recu_finder(sl, map, x, y - 1);
	recu_finder(sl, map, x, y + 1);
	return (0);
}

int	verif_map(t_data *sl)
{
	char	*tmp;

	tmp = ft_strdup(sl->map.map);
	if (!tmp)
		return (0);
	if (!verif_map_size(sl) || !verif_count(sl) || !parcour_map(sl))
		return (free(tmp), 0);
	sl->map.pos.x = 0;
	sl->map.pos.y = 0;
	init_pos(sl);
	recu_finder(sl, tmp, sl->entities[0].pos.x / 128, sl->entities[0].pos.y / 128);
	if (is_still(tmp))
		return (free(tmp), 0);
	complete_border(sl, 0, 0);
	printf("%s\n", sl->map.map);
	return (free(tmp), 1);
}
