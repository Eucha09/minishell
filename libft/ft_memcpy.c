/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:14:14 by yim               #+#    #+#             */
/*   Updated: 2022/11/11 14:38:32 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp;
	const char		*s;

	if (n == 0 || dst == src)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	tmp = dst;
	s = src;
	while (n)
	{
		*tmp++ = *s++;
		n--;
	}
	return (dst);
}
