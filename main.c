/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:54:37 by jcoquard          #+#    #+#             */
/*   Updated: 2023/09/03 19:04:05 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/so_long.h"

int	main(int ac, char **av)
{
	t_data	so_long;

	init_window(&so_long, WIN_W, WIN_H);
	if (ac != 2)
		error(&so_long, ERR_ARG);
	if (!load_map(&so_long, av[1]))
		error(&so_long, ERR_MAP);
	load_all_image(&so_long);
	map_to_img(&so_long);
	mlx_hook(so_long.win.win, 2, 1L << 0, key_press, &so_long);
	mlx_hook(so_long.win.win, 3, 1L << 1, key_release, &so_long);
	mlx_hook(so_long.win.win, 17, 1L << 0, close_window, &so_long);
	mlx_loop_hook(so_long.win.mlx, event_manager, &so_long);
	mlx_loop(so_long.win.mlx);
	return (0);
}
