/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:31:02 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/15 14:47:06 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <stdlib.h>

int	code_error(char *str, int errno);
int	free_code_error(char *free_str, int i);
int	free_return(char *tmp, char *tmp2, int num);

#endif