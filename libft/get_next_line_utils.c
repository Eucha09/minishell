/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:05:10 by yim               #+#    #+#             */
/*   Updated: 2023/01/16 15:45:13 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}	

int	check_newline(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (-1);
		i++;
	}
	return (i + 1);
}

char	*gnl_ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	unsigned int	s_len;

	if (s == NULL)
		return (NULL);
	s_len = gnl_ft_strlen(s);
	if (s_len < start || s[start] == '\0')
		return (NULL);
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

void	*gnl_ft_memcpy(void *dst, const void *src, size_t n)
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

char	*gnl_ft_strdup(const char *s1)
{
	char	*dest;
	int		s1_len;
	int		i;

	i = 0;
	s1_len = gnl_ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * s1_len + 1);
	if (dest == NULL)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
