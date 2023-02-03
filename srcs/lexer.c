/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:45:53 by jeong-euich       #+#    #+#             */
/*   Updated: 2023/02/03 19:25:05 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*toknew(int size)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (tok == NULL)
		return (NULL);
	tok->data = (char *)malloc(size + 1);
	if (tok->data == NULL)
	{
		free(tok);
		return (NULL);
	}
	ft_memset(tok->data, 0, size + 1);
	tok->type = TOKEN;
	tok->next = NULL;
	return (tok);
}

void	lstadd_tok(t_lexer *lexer, t_token *tok)
{
	t_token	*cur;

	if (lexer->list_tok == NULL)
	{
		lexer->list_tok = tok;
		return ;
	}
	cur = lexer->list_tok;
	while (cur && cur->next)
	{
		cur = cur->next;
	}
	cur->next = tok;
}

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

int	gettok(char *str, int size, t_lexer *lexer)
{
	t_token	*tok;
	int		i;
	int		j;
	char	quote;

	tok = toknew(size);
	if (tok == NULL)
		return (1);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i] && (str[i] != ' ' || quote != 0))
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			tok->data[j++] = str[i];
		i++;
	}
	lstadd_tok(lexer, tok);
	return (i);
}

void	lexer_build(char *str, int size, t_lexer *lexer)
{
	int	i;

	lexer->list_tok = NULL;
	lexer->tok_cnt = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '|')
			i += gettok_pipe(str + i, lexer);
		else if (str[i] == '<')
			i += gettok_lesser(str + i, lexer);
		else if (str[i] == '>')
			i += gettok_greater(str + i, lexer);
		else if (str[i])
		{
			i += gettok(str + i, size - i, lexer);
			lexer->tok_cnt++;
		}
	}
}

void	tok_clear(t_token *tok) {
	if (tok == NULL)
		return ;
	free(tok->data);
	tok_clear(tok->next);
	free(tok);
}

void	lexer_clear(t_lexer *lexer)
{
	if (lexer == NULL)
		return;
	tok_clear(lexer->list_tok);
}
