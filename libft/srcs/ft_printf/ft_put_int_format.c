/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_int_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:27:15 by eujeong           #+#    #+#             */
/*   Updated: 2022/09/01 16:00:23 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_int_format(t_format *format, int num)
{
	int		ret;
	int		unum_len;
	int		p_len;
	int		sign;
	t_uint	unum;

	ret = 0;
	unum = ft_abs(num);
	sign = 0;
	if (num < 0)
		sign = -1;
	else if ((format->flag & FLAG_PLUS) + (format->flag & FLAG_SPACE))
		sign = 1;
	if (sign != 0 && format->flag & FLAG_ZERO && format->width > 1)
		format->prec += format->width;
	unum_len = ft_uint_len_prec(unum, format->prec);
	p_len = format->width - (int)ft_abs(sign) - unum_len;
	if (!(format->flag & FLAG_MINUS) && p_len > 0)
		ret += ft_put_padding(p_len, (format->flag & FLAG_ZERO));
	ret += ft_put_sign(sign, format->flag);
	ret += ft_putnbr_prec(unum, format->prec);
	if ((format->flag & FLAG_MINUS) && p_len > 0)
		ret += ft_put_padding(p_len, 0);
	return (ret);
}
