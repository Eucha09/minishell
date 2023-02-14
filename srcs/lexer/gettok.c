/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:49:57 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/14 14:16:50 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	gettok_pipe(char *str, t_lexer *lexer)
{
	t_token	*tok;

	tok = toknew(1);
	if (tok == NULL)
		return (1);
	if (str[0] == '|')
		tok->data[0] = str[0];
	tok->type = TOKEN_PIPE;
	lstadd_tok(lexer, tok);
	return (1);
}

int	gettok_lesser(char *str, t_lexer *lexer)
{
	t_token	*tok;

	tok = toknew(2);
	if (tok == NULL)
		return (1);
	if (str[0] == '<')
	{
		tok->data[0] = str[0];
		tok->type = TOKEN_LESS;
	}
	if (str[1] == '<')
	{
		tok->data[1] = str[1];
		tok->type = TOKEN_DLESS;
	}
	lstadd_tok(lexer, tok);
	return (ft_strlen(tok->data));
}

int	gettok_greater(char *str, t_lexer *lexer)
{
	t_token	*tok;

	tok = toknew(2);
	if (tok == NULL)
		return (1);
	if (str[0] == '>')
	{
		tok->data[0] = str[0];
		tok->type = TOKEN_GREAT;
	}
	if (str[1] == '>')
	{
		tok->data[1] = str[1];
		tok->type = TOKEN_DGREAT;
	}
	lstadd_tok(lexer, tok);
	return (ft_strlen(tok->data));
}

int	gettok(char *str, int size, t_lexer *lexer, char *envp[])
{
	t_token	*tok;
	int		i;
	char	quote;

	tok = toknew(size);
	if (tok == NULL)
		return (1);
	i = 0;
	quote = 0;
	while (str[i] && (!isprs(str[i]) || quote != 0))
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		tok->data[i] = str[i];
		i++;
	}
	expand_tok(tok, i, envp);
	lstadd_tok(lexer, tok);
	return (i);
}
