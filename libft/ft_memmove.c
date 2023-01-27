/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:23:39 by yim               #+#    #+#             */
/*   Updated: 2022/11/11 14:38:46 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp;
	const char		*s;

	if (len == 0 || dst == src)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst <= src)
	{
		tmp = dst;
		s = src;
		while (len--)
			*tmp++ = *s++;
	}
	else
	{
		tmp = dst + len;
		s = src + len;
		while (len--)
			*--tmp = *--s;
	}
	return (dst);
}
