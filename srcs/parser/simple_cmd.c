/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:48:36 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/30 16:51:32 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*simplecmd1(t_token **curtok)
{
	t_astnode	*arglistnode;
	t_astnode	*ret;
	char		*cmdpath;

	if (!term(curtok, TOKEN, &cmdpath))
		return (NULL);
	arglistnode = arglist(curtok);
	if (arglistnode == NULL)
	{
		free(cmdpath);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, cmdpath, NODE_CMDPATH);
	astnode_attach(ret, NULL, arglistnode);
	return (ret);
}

t_astnode	*simplecmd2(t_token	**curtok)
{
	t_astnode	*ret;
	char		*cmdpath;

	if (!term(curtok, TOKEN, &cmdpath))
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, cmdpath, NODE_CMDPATH);
	return (ret);
}

t_astnode	*simplecmd(t_token **curtok)
{
	t_token		*save;
	t_astnode	*node;

	save = *curtok;
	node = simplecmd1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = simplecmd2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}
