/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:20:25 by yim               #+#    #+#             */
/*   Updated: 2022/11/08 15:44:20 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	tmp;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		tmp = 0;
		if (haystack[i] == needle[tmp])
		{
			while (haystack[i + tmp] && needle[tmp])
			{
				if (needle[tmp] != haystack[i + tmp] || (i + tmp) >= len)
					break ;
				tmp++;
			}
			if (needle[tmp] == '\0')
				return (&((char *)haystack)[i]);
		}
		i++;
	}
	return (NULL);
}
