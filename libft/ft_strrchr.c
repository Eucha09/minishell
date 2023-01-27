/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:14:07 by yim               #+#    #+#             */
/*   Updated: 2022/11/09 15:53:51 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	s_len;

	s_len = ft_strlen(s);
	while (s_len != 0 && s[s_len] != (unsigned char)c)
		s_len--;
	if (s[s_len] == (unsigned char)c)
		return ((char *)(s + s_len));
	return (NULL);
}
