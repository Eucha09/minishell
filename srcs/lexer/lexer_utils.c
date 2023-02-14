/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:51:33 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/14 17:02:21 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	isprs(char c)
{
	if (c == '|' || c == '<' || c == '>' || ft_isspace(c))
		return (1);
	return (0);
}

int	isalnum_(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}
