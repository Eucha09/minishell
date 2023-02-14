/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:57:14 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/14 17:02:46 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int	replace_env(char **str, int pos, int size, char *envp[])
{
	char	*new_str;
	char	*env_value;
	int		key_len;
	int		value_len;
	int		new_size;

	key_len = env_key_len(*str + pos + 1);
	env_value = get_env_value(*str + pos + 1, key_len, envp);
	value_len = ft_strlen(env_value);
	new_size = size + value_len + 1;
	new_str = (char *)malloc(sizeof(char) * new_size);
	if (new_str == NULL)
		return (0);
	ft_strlcpy(new_str, (*str), pos + 1);
	ft_strlcat(new_str, env_value, new_size);
	ft_strlcat(new_str, (*str) + pos + 1 + key_len, new_size);
	free(*str);
	*str = new_str;
	return (value_len);
}
