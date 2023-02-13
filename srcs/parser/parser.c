/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:40:31 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/13 18:22:22 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	term(t_token **curtok, int tok_type, char **buffer)
{
	int	size;
	
	if (*curtok == NULL)
		return (0);
	if ((*curtok)->type == tok_type)
	{
		if (buffer != NULL)
		{
			size = ft_strlen((*curtok)->data) + 1;
			*buffer = (char *)malloc(size);
			if (*buffer == NULL)
				return (0);
			ft_strlcpy(*buffer, (*curtok)->data, size);
		}
		*curtok = (*curtok)->next;
		return (1);
	}
	*curtok = (*curtok)->next;
	return (0);
}

int	parse(t_lexer *lexer, t_astnode **astree)
{
	t_token	*curtok;

	if (lexer->list_tok == NULL)
	{
		*astree = NULL;
		return (0);
	}
	curtok = lexer->list_tok;
	*astree = cmdline(&curtok);

	// 에러처리 todo
	if (curtok != NULL || *astree == NULL)
	{
		ft_printf("Syntax Error\n");
		return (0);
	}

	return (1);
}
