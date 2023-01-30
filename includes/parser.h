/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:40:34 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/30 16:45:09 by eujeong          ###   ########.fr       */
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
t_astnode	*cmd1(t_token **curtok);
t_astnode	*cmd2(t_token **curtok);

t_astnode	*simplecmd(t_token **curtok);
t_astnode	*simplecmd1(t_token	**curtok);
t_astnode	*simplecmd2(t_token **curtok);

t_astnode	*redirectlist(t_token **curtok);
t_astnode	*redirectlist1(t_token **curtok);
t_astnode	*redirectlist2(t_token **curtok);

t_astnode	*ioredirect(t_token **curtok);
t_astnode	*ioredirect1(t_token **curtok);
t_astnode	*ioredirect2(t_token **curtok);
t_astnode	*ioredirect3(t_token **curtok);
t_astnode	*ioredirect4(t_token **curtok);

t_astnode	*arglist(t_token **curtok);
t_astnode	*arglist1(t_token **curtok);
t_astnode	*arglist2(t_token **curtok);

#endif