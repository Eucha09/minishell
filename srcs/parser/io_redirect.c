/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:48:25 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/30 15:49:56 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*ioredirect1(t_token **curtok)
{
	t_astnode	*ret;
	char		*filename;

	if (!term(curtok, TOKEN_GREAT, NULL))
		return (NULL);
	if (!term(curtok, TOKEN, &filename))
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, filename, NODE_REDIRECT_OUT);
	return (ret);
}

t_astnode	*ioredirect2(t_token **curtok)
{
	t_astnode	*ret;
	char		*filename;

	if (!term(curtok, TOKEN_LESS, NULL))
		return (NULL);
	if (!term(curtok, TOKEN, &filename))
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, filename, NODE_REDIRECT_IN);
	return (ret);
}

t_astnode	*ioredirect3(t_token **curtok)
{
	t_astnode	*ret;
	char		*filename;

	if (!term(curtok, TOKEN_DGREAT, NULL))
		return (NULL);
	if (!term(curtok, TOKEN, &filename))
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, filename, NODE_DREDIRECT_OUT);
	return (ret);
}

t_astnode	*ioredirect4(t_token **curtok)
{
	t_astnode	*ret;
	char		*here_end;

	if (!term(curtok, TOKEN_DLESS, NULL))
		return (NULL);
	if (!term(curtok, TOKEN, &here_end))
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, here_end, NODE_DREDIRECT_IN);
	return (ret);
}

t_astnode	*ioredirect(t_token **curtok)
{
	t_token		*save;
	t_astnode	*node;

	save = *curtok;
	node = ioredirect1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = ioredirect2(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = ioredirect3(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = ioredirect4(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}
