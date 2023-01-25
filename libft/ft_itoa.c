/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:43:45 by yim               #+#    #+#             */
/*   Updated: 2022/11/11 13:34:57 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_digit(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count++;
	while (n)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*ft_strrev(char *str)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

static char	*make_itoa(long long long_n, int digit, int sign)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc(sizeof(char) * digit + 1);
	if (result == NULL)
		return (NULL);
	while (long_n)
	{
		result[i++] = (long_n % 10) + '0';
		long_n /= 10;
	}
	if (sign == -1)
	{
		result[i] = '-';
		i++;
	}
	result[i] = '\0';
	return (ft_strrev(result));
}

char	*ft_itoa(int n)
{
	int			digit;
	long long	long_n;
	char		*result;
	int			sign;

	sign = 0;
	digit = check_digit(n);
	long_n = (long long)n;
	if (n == 0)
		return (ft_strdup("0"));
	if (long_n < 0)
	{
		sign = -1;
		long_n *= -1;
	}
	result = make_itoa(long_n, digit, sign);
	return (result);
}
