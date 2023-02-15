/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:36:02 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/15 15:00:50 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*toknew(int size)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (tok == NULL)
	{
		code_error("malloc error", 1);
		return (NULL);
	}
	tok->data = (char *)malloc(size + 1);
	if (tok->data == NULL)
	{
		code_error("malloc error", 1);
		free(tok);
		return (NULL);
	}
	ft_memset(tok->data, 0, size + 1);
	tok->type = TOKEN_WORD;
	tok->next = NULL;
	return (tok);
}

void	tok_clear(t_token *tok)
{
	if (tok == NULL)
		return ;
	free(tok->data);
	tok_clear(tok->next);
	free(tok);
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
