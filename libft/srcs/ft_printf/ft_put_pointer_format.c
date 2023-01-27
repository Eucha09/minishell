/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pointer_format.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:26:28 by eujeong           #+#    #+#             */
/*   Updated: 2022/09/01 16:32:39 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_pointer_format(t_format *format, t_ulong p)
{
	int	ret;
	int	pointer_len;

	ret = 0;
	pointer_len = ft_nbrlen_hex_prec(p, format->prec);
	if (!(format->flag & FLAG_MINUS) && format->width - 2 - pointer_len > 0)
		ret += ft_put_padding(format->width - 2 - pointer_len, 0);
	ret += ft_put_zero_x('x');
	ret += ft_putnbr_hex_prec(p, HEX_LOW, -1);
	if ((format->flag & FLAG_MINUS) && format->width - 2 - pointer_len > 0)
		ret += ft_put_padding(format->width - 2 - pointer_len, 0);
	return (ret);
}
