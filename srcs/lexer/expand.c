/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:52:57 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/15 14:19:59 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_errno;

int	replace_errno(char **str, int pos, int size)
{
	char	*new_str;
	char	*errno_str;
	int		errno_len;
	int		new_size;

	errno_str = ft_itoa(g_errno);
	if (errno_str == NULL)
		return (0);
	errno_len = ft_strlen(errno_str);
	new_size = size + errno_len + 1;
	new_str = (char *)malloc(sizeof(char) * new_size);
	if (new_str == NULL)
		return (0);
	ft_strlcpy(new_str, (*str), pos + 1);
	ft_strlcat(new_str, errno_str, new_size);
	ft_strlcat(new_str, (*str) + pos + 2, new_size);
	free(*str);
	free(errno_str);
	*str = new_str;
	return (errno_len);
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
		if ((*str)[i] == '$' && (*str)[i + 1] == '?' && quote != '\'')
			i += replace_errno(str, i, size);
		else if ((*str)[i] == '$' && isalnum_((*str)[i + 1]) && quote != '\'')
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
