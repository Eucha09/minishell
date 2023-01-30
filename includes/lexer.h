/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:03:39 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/29 21:22:54 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define TOKEN			0
# define TOKEN_PIPE		1
# define TOKEN_LESS		2
# define TOKEN_DLESS	3
# define TOKEN_GREAT	4
# define TOKEN_DGREAT	5

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token	*list_tok;
	int	tok_cnt;
}	t_lexer;

void	lexer_build(char *str, int size, t_lexer *lexer);
void	lexer_clear(t_lexer *lexer);

#endif