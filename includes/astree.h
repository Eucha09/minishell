/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:44:20 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/02 13:49:35 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# include <stdlib.h>

# define NODE_PIPE			1
# define NODE_SIMPLE_CMD	2
# define NODE_CMD_PREFIX	3
# define NODE_CMD_SUFFIX	4
# define NODE_REDIRECT_IN	5
# define NODE_DREDIRECT_IN	6
# define NODE_REDIRECT_OUT	7
# define NODE_DREDIRECT_OUT	8

typedef struct s_astnode
{
    int					type;
    char				*data;
    struct s_astnode*	left;
    struct s_astnode*	right;

}	t_astnode;

t_astnode	*astnode_new(void);
void		astnode_attach(t_astnode *root, t_astnode *left, t_astnode *right);
void		astnode_init(t_astnode *node, char *data, int type);
void		astnode_delete(t_astnode *node);

#endif