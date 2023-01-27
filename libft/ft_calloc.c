/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:20:48 by yim               #+#    #+#             */
/*   Updated: 2022/11/13 20:05:34 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(size * count);
	if (str == NULL)
		return (NULL);
	while (i < count * size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
