/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:41:13 by yim               #+#    #+#             */
/*   Updated: 2022/11/09 15:36:51 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	unsigned int	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		return (ft_strdup(""));
	i = 0;
	if (len < s_len - start + 1)
		dest = (char *)malloc(sizeof(char) * (len + 1));
	else
		dest = (char *)malloc(sizeof(char) * (s_len - start + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len && i < s_len - start)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
