/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:15:53 by yim               #+#    #+#             */
/*   Updated: 2023/01/06 18:50:17 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char a, char c)
{
	if (c == a)
		return (1);
	return (0);
}

static int	ft_word_cnt(char const *s, char c)
{
	int	i;
	int	word_cnt;

	i = 0;
	word_cnt = 0;
	while (s[i])
	{
		while (s[i] && is_charset(s[i], c))
			i++;
		if (s[i])
			word_cnt++;
		while (s[i] && !is_charset(s[i], c))
			i++;
	}
	return (word_cnt);
}

static int	ft_word_len(char const *s, char c)
{
	int	word_len;

	word_len = 0;
	while (s[word_len] && (!is_charset(s[word_len], c)))
		word_len++;
	return (word_len);
}

static char	**ft_make_split(char const *s, char c, char **str_arr)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && is_charset(*s, c))
			s++;
		if (*s)
		{
			str_arr[i] = ft_substr(s, 0, ft_word_len(s, c));
			if (str_arr[i] == NULL)
			{
				i = -1;
				while (str_arr[++i])
					free(str_arr[i]);
				free(str_arr);
				return (NULL);
			}
			i++;
		}
		while (*s && !is_charset(*s, c))
			s++;
	}
	str_arr[i] = 0;
	return (str_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	int		word_cnt;

	word_cnt = ft_word_cnt(s, c);
	str_arr = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (str_arr == NULL)
		return (NULL);
	str_arr = ft_make_split(s, c, str_arr);
	return (str_arr);
}
