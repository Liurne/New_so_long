/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:09:46 by jcoquard          #+#    #+#             */
/*   Updated: 2024/02/20 18:44:35 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H
# include "../minilibx/mlx.h"
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# define ERR_MLX "Couldn't initiate mlx"
# define ERR_ARG "Invalid number of argument"
# define ERR_LIB "Couldn't create a window"
# define ERR_MAP "Map invalid or non-existant"
# define ERR_TEX "Texture invalid or non-existant"
# define ERR_IMG "Couldn't creater an image"
# define WIN_W 1280
# define WIN_H 768
# define C_NIGHT 0xFF001835

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_w;
	int		img_h;
}	t_img;

typedef struct s_wins
{
	void	*mlx;
	void	*win;
	t_img	renderer;
	int		w;
	int		h;
}	t_wins;

typedef struct s_vec
{
	int	x;
	int	y;
}	t_vec;

typedef struct s_map
{
	char	*map;
	int		w;
	int		h;
	t_vec	pos;
	t_vec	start;
	t_vec	end;
	t_img	img;
	t_img	tex[57];
}	t_map;

typedef enum e_mob
{
	PLAYER,
	DOG,
	WOLF
}	t_mob;

typedef struct s_entity
{
	int		id;
	t_mob	type;
	int		alive;
	t_vec	pos;
	t_vec	tpos;
	int		w;
	int		h;
	int		dir;
	size_t	nb_mv;
	size_t	dist;
	int		delay;
	int		inmove;
	int		animation;
}	t_entity;

typedef struct s_keyboard
{
	int	up;
	int	down;
	int	left;
	int	right;
}	t_keyboard;

typedef struct s_data
{
	t_wins		win;
	t_keyboard	keys;
	t_map		map;
	size_t		nb_tile;
	size_t		nb_dogs;
	t_entity	pl;
	t_entity	wolf;
	t_entity	*entities;
	t_img		tex_pl[5][4];
	t_img		tex_dog[5][4];
	t_img		tex_wolf[5][4];
	int			trans;
	int			show_hitbox;
	int			time;
}	t_data;

#endif