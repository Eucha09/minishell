/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_char_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:22:59 by eujeong           #+#    #+#             */
/*   Updated: 2022/09/01 16:15:32 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_char_format(t_format *format, int c)
{
	int	ret;

	ret = 0;
	if (!(format->flag & FLAG_MINUS) && format->width - 1 > 0)
		ret += ft_put_padding(format->width - 1, 0);
	ft_putchar_fd((char)c, 1);
	ret += 1;
	if (format->flag & FLAG_MINUS && format->width - 1 > 0)
		ret += ft_put_padding(format->width - 1, 0);
	return (ret);
}
