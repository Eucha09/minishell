/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:11:56 by eujeong           #+#    #+#             */
/*   Updated: 2022/09/01 15:47:50 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_set_flag(t_format *format, char c)
{
	if (c == '-')
		format->flag |= FLAG_MINUS;
	else if (c == '+')
		format->flag |= FLAG_PLUS;
	else if (c == ' ')
		format->flag |= FLAG_SPACE;
	else if (c == '#')
		format->flag |= FLAG_NUMBERSIGN;
	else if (c == '0')
		format->flag |= FLAG_ZERO;
}

void	ft_set_format(t_format *format, char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr(FORMAT_TPYE, str[i]) && str[i])
	{
		if (ft_strchr(FLAGS, str[i]))
			ft_set_flag(format, str[i++]);
		else if (ft_isdigit(str[i]))
		{
			format->width = ft_atoi(str + i);
			i += ft_disits_len(str + i);
		}
		else if (str[i] == '.')
		{
			format->flag &= ~FLAG_ZERO;
			format->prec = ft_atoi(str + i + 1);
			i += 1 + ft_disits_len(str + i + 1);
		}
	}
	format->type = str[i];
}

int	ft_put_format(char *str, va_list ap)
{
	int			ret;
	t_format	format;

	ret = 0;
	ft_memset(&format, 0, sizeof(format));
	format.prec = -1;
	if (str[0] != '%')
		return (0);
	ft_set_format(&format, str + 1);
	ret = ft_put_data(&format, ap);
	return (ret);
}

int	ft_format_len(char *str)
{
	int	i;

	if (str[0] != '%')
		return (0);
	i = 1;
	while (!ft_strchr(FORMAT_TPYE, str[i]) && str[i])
		i++;
	if (str[i] && ft_strchr(FORMAT_TPYE, str[i]))
		return (i + 1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		ret;
	int		i;
	va_list	ap;

	va_start(ap, str);
	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			ret += ft_put_format((char *)str + i, ap);
			i += ft_format_len((char *)str + i);
		}
		else
		{
			ft_putchar_fd(str[i++], 1);
			ret++;
		}
	}
	va_end(ap);
	return (ret);
}
