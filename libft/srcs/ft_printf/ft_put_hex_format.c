/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:25:57 by eujeong           #+#    #+#             */
/*   Updated: 2022/09/01 16:31:51 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_hex_format(t_format *format, t_uint unum)
{
	int	ret;
	int	unum_len;
	int	p_len;

	ret = 0;
	if (format->flag & FLAG_NUMBERSIGN && format->flag & FLAG_ZERO && unum != 0)
		format->prec = format->width - 2;
	unum_len = ft_nbrlen_hex_prec((t_ulong)unum, format->prec);
	p_len = format->width - unum_len;
	if (format->flag & FLAG_NUMBERSIGN && unum != 0)
		p_len -= 2;
	if (!(format->flag & FLAG_MINUS) && p_len > 0)
		ret += ft_put_padding(p_len, (format->flag & FLAG_ZERO));
	if (format->flag & FLAG_NUMBERSIGN && unum != 0)
		ret += ft_put_zero_x(format->type);
	if (format->type == 'x')
		ret += ft_putnbr_hex_prec((t_ulong)unum, HEX_LOW, format->prec);
	else
		ret += ft_putnbr_hex_prec((t_ulong)unum, HEX_UPP, format->prec);
	if ((format->flag & FLAG_MINUS) && p_len > 0)
		ret += ft_put_padding(p_len, 0);
	return (ret);
}
