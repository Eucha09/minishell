/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:38:15 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/10 17:05:05 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*cmdprefix1(t_token **curtok)
{
	t_astnode	*ioredirectnode;
	t_astnode	*cmdprefixnode;
	t_astnode	*ret;

	ioredirectnode = ioredirect(curtok);
	if (ioredirectnode == NULL)
		return (NULL);
	cmdprefixnode = cmdprefix(curtok);
	if (cmdprefixnode == NULL)
	{
		astnode_delete(ioredirectnode);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, NULL, NODE_CMD_PREFIX);
	astnode_attach(ret, ioredirectnode, cmdprefixnode);
	return (ret);
}

t_astnode	*cmdprefix2(t_token **curtok)
{
	t_astnode	*ioredirectnode;
	t_astnode	*ret;

	ioredirectnode = ioredirect(curtok);
	if (ioredirectnode == NULL)
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, NULL, NODE_CMD_PREFIX);
	astnode_attach(ret, ioredirectnode, NULL);
	return (ret);
}

t_astnode	*cmdprefix(t_token **curtok)
{
	t_token		*save;
	t_astnode	*node;

	save = *curtok;
	node = cmdprefix1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = cmdprefix2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}
