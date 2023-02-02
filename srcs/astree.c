/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:40:28 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/30 20:28:36 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"

t_astnode	*astnode_new(void)
{
	t_astnode	*node;

	node = (t_astnode *)malloc(sizeof(t_astnode));
	if (node == NULL)
		return (NULL);
	node->data = NULL;
	node->type = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	astnode_attach(t_astnode *root, t_astnode *left, t_astnode *right)
{
	if (root == NULL)
		;//에러
	root->left = left;
	root->right = right;
}

void	astnode_init(t_astnode *node, char *data, int type)
{
	if (node == NULL)
		;//에러
	node->data = data;
	node->type = type;
}

void	astnode_delete(t_astnode *node)
{
	if (node == NULL)
		return ;
	free(node->data);
	astnode_delete(node->left);
	astnode_delete(node->right);
	free(node);
}