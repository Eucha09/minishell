/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:07:15 by eujeong           #+#    #+#             */
/*   Updated: 2022/09/01 16:22:57 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_disits_len(char *str)
{
	int	len;

	len = 0;
	while (ft_isdigit(str[len]))
		len++;
	return (len);
}

int	ft_uint_len_prec(t_uint nbr, int prec)
{
	int	len;

	len = 0;
	if (nbr == 0 && prec != 0)
		len++;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	len = ft_max(len, prec);
	return (len);
}

int	ft_nbrlen_hex_prec(t_ulong nbr, int prec)
{
	int	len;

	len = 0;
	if (nbr == 0 && prec != 0)
		len++;
	while (nbr != 0)
	{
		len++;
		nbr /= 16;
	}
	len = ft_max(len, prec);
	return (len);
}
