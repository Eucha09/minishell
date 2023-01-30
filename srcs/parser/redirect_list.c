/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:48:29 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/30 16:43:48 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*redirectlist1(t_token **curtok)
{
	t_astnode	*ioredirectnode;
	t_astnode	*redirectlistnode;
	t_astnode	*ret;

	ioredirectnode = ioredirect(curtok);
	if (ioredirectnode == NULL)
		return (NULL);
	redirectlistnode = redirectlist(curtok);
	if (redirectlistnode == NULL)
	{
		astnode_delete(ioredirectnode);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, NULL, NODE_REDIRECTS);
	astnode_attach(ret, ioredirectnode, redirectlistnode);
	return (ret);
}

t_astnode	*redirectlist2(t_token **curtok)
{
	return (ioredirect(curtok));
}

t_astnode	*redirectlist(t_token **curtok)
{
	t_token		*save;
	t_astnode	*node;

	save = *curtok;
	node = redirectlist1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = redirectlist2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}
