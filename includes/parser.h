/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:40:34 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/03 19:45:24 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "astree.h"
# include "lexer.h"

int			parse(t_lexer *lexer, t_astnode **astree);
int			term(t_token **curtok, int tok_type, char **buffer);

t_astnode	*cmdline(t_token **curtok);
t_astnode	*cmdline1(t_token **curtok);
t_astnode	*cmdline2(t_token **curtok);

t_astnode	*cmd(t_token **curtok);

t_astnode	*simplecmd(t_token **curtok);
t_astnode	*simplecmd1(t_token	**curtok);
t_astnode	*simplecmd2(t_token **curtok);
t_astnode	*simplecmd3(t_token **curtok);
t_astnode	*simplecmd4(t_token **curtok);
t_astnode	*simplecmd5(t_token **curtok);

t_astnode	*cmdprefix(t_token **curtok);
t_astnode	*cmdprefix1(t_token **curtok);
t_astnode	*cmdprefix2(t_token **curtok);

t_astnode	*cmdsuffix(t_token **curtok);
t_astnode	*cmdsuffix1(t_token **curtok);
t_astnode	*cmdsuffix2(t_token **curtok);
t_astnode	*cmdsuffix3(t_token **curtok);
t_astnode	*cmdsuffix4(t_token **curtok);

t_astnode	*ioredirect(t_token **curtok);
t_astnode	*ioredirect1(t_token **curtok);
t_astnode	*ioredirect2(t_token **curtok);
t_astnode	*ioredirect3(t_token **curtok);
t_astnode	*ioredirect4(t_token **curtok);

#endif