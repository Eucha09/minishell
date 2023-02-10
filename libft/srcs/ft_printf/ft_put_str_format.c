/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_str_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:27:33 by eujeong           #+#    #+#             */
/*   Updated: 2022/09/01 16:17:43 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_str_format(t_format *format, char *str)
{
	int		ret;
	size_t	len;
	size_t	i;

	ret = 0;
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (format->prec > -1 && format->prec < (int)len)
		len = format->prec;
	if (!(format->flag & FLAG_MINUS) && format->width - (int)len > 0)
		ret += ft_put_padding(format->width - len, 0);
	i = 0;
	while (i < len)
		ft_putchar_fd(str[i++], 1);
	ret += len;
	if (format->flag & FLAG_MINUS && format->width - (int)len > 0)
		ret += ft_put_padding(format->width - len, 0);
	return (ret);
}
