/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:51:33 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/14 13:52:31 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	isprs(char c)
{
	if (c == '|' || c == '<' || c == '>' || ft_isspace(c))
		return (1);
	return (0);
}

int	isalnum_(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	env_key_len(char *key)
{
	int	len;

	len = 0;
	if (ft_isdigit(key[0]))
		return (1);
	while (isalnum_(key[len]))
		len++;
	return (len);
}

char	*get_env_value(char *key, int len, char *envp[])
{
	int		i;
	char	temp;

	temp = key[len];
	key[len] = '=';
	i = 0;
	while(envp[i])
	{
		if (ft_strncmp(key, envp[i], len + 1) == 0)
		{
			key[len] = temp;
			return (envp[i] + len + 1);
		}
		i++;
	}
	key[len] = temp;
	return ("");
}

