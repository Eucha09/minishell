/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:48:18 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/14 15:57:53 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astnode	*cmd(t_token **curtok)
{
	return (simplecmd(curtok));
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
	*curtok = save;
	node = simplecmd3(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = simplecmd4(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = simplecmd5(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}
