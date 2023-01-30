/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:44:20 by eujeong           #+#    #+#             */
/*   Updated: 2023/01/30 15:05:54 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# include <stdlib.h>

# define NODE_PIPE			(1 << 0)
# define NODE_REDIRECTS		(1 << 1)
# define NODE_REDIRECT_IN	(1 << 2)
# define NODE_DREDIRECT_IN	(1 << 3)
# define NODE_REDIRECT_OUT	(1 << 4)
# define NODE_DREDIRECT_OUT	(1 << 5)
# define NODE_CMDPATH		(1 << 6)
# define NODE_ARG			(1 << 7)
//# define NODE_DATA		(1 << 7)

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