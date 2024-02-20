/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:37:46 by jcoquard          #+#    #+#             */
/*   Updated: 2024/02/20 18:05:24 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "define.h"

/* -----utils----- */
size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strber(const char *haystack);
void	ft_putmove_fd(int nb_move, int fd);
void	*ft_calloc(size_t count, size_t size);
char	*ft_itoa(int n);

/* -----init----- */
int		init_window(t_data *sl, int win_w, int win_h);
int		close_window(t_data *sl);
int		new_img(t_data *sl, t_img *img, int w, int h);
int		load_img(t_data *sl, char *path, t_img *img);
int		destroy_img(t_data *sl, t_img *img);
void	load_all_image(t_data *sl);
void	destroy_all_image(t_data *sl);
int		error(t_data *sl, char *msg);

/* -----parsing----- */
int		load_map(t_data *sl, char *path);
int		verif_map(t_data *sl);
void	complete_border(t_data *sl, int x, int y);
int		is_still(char *map);

/* -----world----- */
char	get_tile(t_data *sl, int x, int y);
int		set_tile(t_data *sl, int x, int y, char c);
void	put_pixelmap(t_map *m, int x, int y, int img);
int		map_to_img(t_data *sl);
void	reload_tile_img(t_data *sl, int x, int y);
void	which_border(t_data *sl, t_map *map, int x, int y);

/* -----entity----- */
void	init_pos(t_data *sl);
int		map_collision(t_data *sl, t_entity *e, int x, int y);
int		entity_collision(t_entity *e1, t_entity *e2);
void	player_manager(t_data *sl);
void	dog_manager(t_data *sl, t_entity *e);
void	wolf_manager(t_data *sl, t_entity *e);

/* -----display----- */
void	put_pixel(t_img *img, int x, int y, int color);
int		get_pixel(t_img *img, int x, int y);
int		transparence(int c1, int c2, int t);
void	display_entity(t_data *sl, t_entity *e);
void	display_dog(t_data *sl, t_entity *e);
void	animation(t_data *sl);
void		render_display(t_data *sl);

/* -----event----- */
int		key_press(int keycode, t_data *sl);
int		key_release(int keycode, t_data *sl);
int		event_manager(t_data *sl);

#endif