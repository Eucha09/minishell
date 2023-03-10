/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:48:36 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/15 14:56:24 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*simplecmd1(t_token **curtok)
{
	t_astnode	*cmdprefixnode;
	t_astnode	*cmdsuffixnode;
	t_astnode	*ret;
	char		*cmdpath;

	cmdprefixnode = cmdprefix(curtok);
	if (cmdprefixnode == NULL)
		return (NULL);
	if (!term(curtok, TOKEN_WORD, &cmdpath))
	{
		astnode_delete(cmdprefixnode);
		return (NULL);
	}
	cmdsuffixnode = cmdsuffix(curtok);
	if (cmdsuffixnode == NULL)
	{
		astnode_delete(cmdprefixnode);
		free(cmdpath);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, cmdpath, NODE_SIMPLE_CMD);
	astnode_attach(ret, cmdprefixnode, cmdsuffixnode);
	return (ret);
}

t_astnode	*simplecmd2(t_token **curtok)
{
	t_astnode	*cmdprefixnode;
	t_astnode	*ret;
	char		*cmdpath;

	cmdprefixnode = cmdprefix(curtok);
	if (cmdprefixnode == NULL)
		return (NULL);
	if (!term(curtok, TOKEN_WORD, &cmdpath))
	{
		astnode_delete(cmdprefixnode);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, cmdpath, NODE_SIMPLE_CMD);
	astnode_attach(ret, cmdprefixnode, NULL);
	return (ret);
}

t_astnode	*simplecmd3(t_token **curtok)
{
	t_astnode	*cmdprefixnode;
	t_astnode	*ret;

	cmdprefixnode = cmdprefix(curtok);
	if (cmdprefixnode == NULL)
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, NULL, NODE_SIMPLE_CMD);
	astnode_attach(ret, cmdprefixnode, NULL);
	return (ret);
}

t_astnode	*simplecmd4(t_token **curtok)
{
	t_astnode	*cmdsuffixnode;
	t_astnode	*ret;
	char		*cmdpath;

	if (!term(curtok, TOKEN_WORD, &cmdpath))
		return (NULL);
	cmdsuffixnode = cmdsuffix(curtok);
	if (cmdsuffixnode == NULL)
	{
		free(cmdpath);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, cmdpath, NODE_SIMPLE_CMD);
	astnode_attach(ret, NULL, cmdsuffixnode);
	return (ret);
}

t_astnode	*simplecmd5(t_token **curtok)
{
	t_astnode	*ret;
	char		*cmdpath;

	if (!term(curtok, TOKEN_WORD, &cmdpath))
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, cmdpath, NODE_SIMPLE_CMD);
	astnode_attach(ret, NULL, NULL);
	return (ret);
}
