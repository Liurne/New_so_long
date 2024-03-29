/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:14:33 by jcoquard          #+#    #+#             */
/*   Updated: 2024/03/26 18:04:10 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putnbr_fd(int n, int fd)
{
	size_t	c;
	int		tmp;

	c = 0;
	tmp = 0;
	if (n == -2147483648)
		tmp += write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n *= -1;
			tmp += write(fd, "-", 1);
		}
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		c = '0' + n % 10;
		tmp += write(fd, &c, 1);
	}
}
