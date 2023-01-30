/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:48:13 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/30 16:44:38 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*arglist1(t_token **curtok)
{
	t_astnode	*arglistnode;
	t_astnode	*ret;
	char		*arg;

	if (!term(curtok, TOKEN, &arg))
		return (NULL);
	arglistnode = arglist(curtok);
	if (arglistnode == NULL)
	{
		free(arg);
		return (NULL);
	}
	ret = astnode_new();
	astnode_init(ret, arg, NODE_ARG);
	astnode_attach(ret, NULL, arglistnode);
	return (ret);
}

t_astnode	*arglist2(t_token **curtok)
{
	t_astnode	*ret;
	char		*arg;

	if (!term(curtok, TOKEN, &arg))
		return (NULL);
	ret = astnode_new();
	astnode_init(ret, arg, NODE_ARG);
	return (ret);
}

t_astnode	*arglist(t_token **curtok)
{
	t_token		*save;
	t_astnode	*node;

	save = *curtok;
	node = arglist1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = arglist2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}
