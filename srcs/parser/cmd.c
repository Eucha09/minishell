/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:48:18 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/30 16:43:24 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*cmd1(t_token **curtok)
{
	t_astnode	*simplecmdnode;
	t_astnode	*redirectlistnode;
	t_astnode	*ret;

	simplecmdnode = simplecmd(curtok);
	if (simplecmdnode == NULL)
		return (NULL);
	redirectlistnode = redirectlist(curtok);
	if (redirectlistnode == NULL)
	{
		astnode_delete(simplecmdnode);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, NULL, NODE_REDIRECTS);
	astnode_attach(ret, redirectlistnode, simplecmdnode);
	return (ret);
}

t_astnode	*cmd2(t_token **curtok)
{
	return (simplecmd(curtok));
}

t_astnode	*cmd(t_token **curtok)
{
	t_token		*save;
	t_astnode	*node;

	save = *curtok;
	node = cmd1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = cmd2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}
