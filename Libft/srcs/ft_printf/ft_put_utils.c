/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:33:37 by eujeong           #+#    #+#             */
/*   Updated: 2022/09/01 16:29:41 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_padding(int size, int flag_zero)
{
	int		i;
	char	c;

	c = ' ';
	if (flag_zero)
		c = '0';
	i = 0;
	while (i++ < size)
		ft_putchar_fd(c, 1);
	return (size);
}

int	ft_put_sign(int sign, int flag)
{
	if (sign < 0)
		ft_putchar_fd('-', 1);
	else if (sign > 0 && flag & FLAG_PLUS)
		ft_putchar_fd('+', 1);
	else if (sign > 0 && flag & FLAG_SPACE)
		ft_putchar_fd(' ', 1);
	return ((int)ft_abs(sign));
}

int	ft_putnbr_prec(t_uint unum, int prec)
{
	int	ret;

	ret = 1;
	if (unum == 0 && prec == 0)
		return (0);
	if (unum < 10 && prec <= 1)
	{
		ft_putchar_fd(unum + '0', 1);
		return (1);
	}
	ret += ft_putnbr_prec(unum / 10, prec - 1);
	ft_putchar_fd(unum % 10 + '0', 1);
	return (ret);
}

int	ft_putnbr_hex_prec(t_ulong nbr, char *base, int prec)
{
	int	ret;

	ret = 1;
	if (nbr == 0 && prec == 0)
		return (0);
	if (nbr < 16 && prec <= 1)
	{
		ft_putchar_fd(base[nbr], 1);
		return (1);
	}
	ret += ft_putnbr_hex_prec(nbr / 16, base, prec - 1);
	ft_putchar_fd(base[nbr % 16], 1);
	return (ret);
}

int	ft_put_zero_x(char x)
{
	ft_putchar_fd('0', 1);
	ft_putchar_fd(x, 1);
	return (2);
}
