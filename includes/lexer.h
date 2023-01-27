/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:03:39 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/27 15:40:30 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define TYPE_TOKEN			0
# define TYPE_PIPE			'|'
# define TYPE_REDIRECT_IN	'<'
# define TYPE_REDIRECT_OUT	'>'

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