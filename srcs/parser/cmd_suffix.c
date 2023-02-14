/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:51:39 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/14 15:57:20 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*cmdsuffix1(t_token **curtok)
{
	t_astnode	*ioredirectnode;
	t_astnode	*cmdsuffixnode;
	t_astnode	*ret;

	ioredirectnode = ioredirect(curtok);
	if (ioredirectnode == NULL)
		return (NULL);
	cmdsuffixnode = cmdsuffix(curtok);
	if (cmdsuffixnode == NULL)
	{
		astnode_delete(ioredirectnode);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, NULL, NODE_CMD_SUFFIX);
	astnode_attach(ret, ioredirectnode, cmdsuffixnode);
	return (ret);
}

t_astnode	*cmdsuffix2(t_token **curtok)
{
	t_astnode	*ioredirectnode;
	t_astnode	*ret;

	ioredirectnode = ioredirect(curtok);
	if (ioredirectnode == NULL)
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, NULL, NODE_CMD_SUFFIX);
	astnode_attach(ret, ioredirectnode, NULL);
	return (ret);
}

t_astnode	*cmdsuffix3(t_token **curtok)
{
	t_astnode	*cmdsuffixnode;
	t_astnode	*ret;
	char		*arg;

	if (!term(curtok, TOKEN_WORD, &arg))
		return (NULL);
	cmdsuffixnode = cmdsuffix(curtok);
	if (cmdsuffixnode == NULL)
	{
		free(arg);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, arg, NODE_CMD_SUFFIX);
	astnode_attach(ret, NULL, cmdsuffixnode);
	return (ret);
}

t_astnode	*cmdsuffix4(t_token **curtok)
{
	t_astnode	*ret;
	char		*arg;

	if (!term(curtok, TOKEN_WORD, &arg))
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, arg, NODE_CMD_SUFFIX);
	return (ret);
}

t_astnode	*cmdsuffix(t_token **curtok)
{
	t_token		*save;
	t_astnode	*node;

	save = *curtok;
	node = cmdsuffix1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = cmdsuffix2(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = cmdsuffix3(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = cmdsuffix4(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}
