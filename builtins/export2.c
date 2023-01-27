/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:31:32 by yim               #+#    #+#             */
/*   Updated: 2023/01/27 20:48:08 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_ep_first(char *str)
{
	if (!ft_isalpha(str[0]))
	{
		if (str[0] != '_')
			return (CODE_ERROR);
	}
	return (CODE_OK);
}

char	*before_equal(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (!(str[i] == '=' || str[i] == '\0'))
		i++;
	result = ft_substr(str, 0, i);
	return (result);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}
