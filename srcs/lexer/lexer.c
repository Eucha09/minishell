/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:45:53 by jeong-euich       #+#    #+#             */
/*   Updated: 2023/02/15 14:20:20 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	strip_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] && (!ft_isspace(str[i]) || quote != 0))
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (str[i])
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

void	lexer_build(char *str, int size, t_lexer *lexer, char *envp[])
{
	t_token	*cur;
	int		i;

	lexer->list_tok = NULL;
	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '|')
			i += gettok_pipe(str + i, lexer);
		else if (str[i] == '<')
			i += gettok_lesser(str + i, lexer);
		else if (str[i] == '>')
			i += gettok_greater(str + i, lexer);
		else if (str[i])
			i += gettok(str + i, size - i, lexer, envp);
	}
	cur = lexer->list_tok;
	while (cur)
	{
		strip_quotes(cur->data);
		cur = cur->next;
	}
}

void	lexer_clear(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	tok_clear(lexer->list_tok);
}
