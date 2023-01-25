/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:14:28 by yim               #+#    #+#             */
/*   Updated: 2022/11/10 11:14:29 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	long_n;
	char	tmp;

	long_n = (long)n;
	if (long_n < 0)
	{
		write(fd, "-", 1);
		long_n *= -1;
	}
	if (long_n / 10)
		ft_putnbr_fd(long_n / 10, fd);
	tmp = long_n % 10 + '0';
	write(fd, &tmp, 1);
}
