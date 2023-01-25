/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:24:34 by yim               #+#    #+#             */
/*   Updated: 2022/11/09 16:03:34 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	p_dest;
	size_t	p_src;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	p_dest = dest_len;
	p_src = 0;
	while (src[p_src] && ((p_src + dest_len + 1) < dstsize))
	{
		dest[p_dest] = src[p_src];
		p_dest++;
		p_src++;
	}
	dest[p_dest] = '\0';
	if (dest_len < dstsize)
		return (src_len + dest_len);
	else
		return (src_len + dstsize);
}
