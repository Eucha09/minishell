/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:47:46 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/30 16:43:04 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*cmdline1(t_token **curtok)
{
	t_astnode	*cmdlinenode;
	t_astnode	*cmdnode;
	t_astnode	*ret;

	cmdnode = cmd(curtok);
	if (cmdnode == NULL)
		return (NULL);
	if (!term(curtok, TOKEN_PIPE, NULL))
	{
		astnode_delete(cmdnode);
		return (NULL);
	}
	cmdlinenode = cmdline(curtok);
	if (cmdlinenode == NULL)
	{
		astnode_delete(cmdnode);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, NULL, NODE_PIPE);
	astnode_attach(ret, cmdnode, cmdlinenode);
	return (ret);
}

t_astnode	*cmdline2(t_token **curtok)
{
	return (cmd(curtok));
}

t_astnode	*cmdline(t_token **curtok)
{
	t_token		*save;
	t_astnode	*node;

	save = *curtok;
	node = cmdline1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = cmdline2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}
