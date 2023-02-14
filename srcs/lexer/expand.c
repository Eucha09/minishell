/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:52:57 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/14 14:19:54 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int	expand_str(char **str, int size, char *envp[])
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while ((*str)[i])
	{
		if (((*str)[i] == '\'' || (*str)[i] == '\"') && quote == 0)
			quote = (*str)[i];
		else if ((*str)[i] == quote)
			quote = 0;
		if ((*str)[i] == '$' && isalnum_((*str)[i + 1]) && quote != '\'')
			i += replace_env(str, i, size, envp);
		else
			i++;
	}
	return (i);
}

int	pos_to_divide(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] && (!ft_isspace(str[i]) || quote != 0))
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

void	divide_tok(t_token *tok, int size)
{
	t_token	*new_tok;
	int i;

	i = pos_to_divide(tok->data);
	if (i < size)
	{
		new_tok = toknew(size - i);
		ft_strlcpy(new_tok->data, tok->data + i, size - i + 1);
		tok->data[i] = '\0';
		tok->next = new_tok;
		divide_tok(new_tok, size - i);
	}
}

void	expand_tok(t_token *tok, int size, char *envp[])
{
	size = expand_str(&(tok->data), size, envp);
	divide_tok(tok, size);
}
