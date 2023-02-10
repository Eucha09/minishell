/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:30:12 by eujeong           #+#    #+#             */
/*   Updated: 2022/09/01 16:32:49 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_data(t_format *format, va_list ap)
{
	if (format->type == 'c')
		return (ft_put_char_format(format, va_arg(ap, int)));
	else if (format->type == 's')
		return (ft_put_str_format(format, va_arg(ap, char *)));
	else if (format->type == 'i' || format->type == 'd')
		return (ft_put_int_format(format, va_arg(ap, int)));
	else if (format->type == 'p')
		return (ft_put_pointer_format(format, va_arg(ap, t_ulong)));
	else if (format->type == 'u')
		return (ft_put_uint_format(format, va_arg(ap, t_uint)));
	else if (format->type == 'x' || format->type == 'X')
		return (ft_put_hex_format(format, va_arg(ap, t_uint)));
	else if (format->type == '%')
		return (ft_put_char_format(format, format->type));
	else
		return (0);
}
