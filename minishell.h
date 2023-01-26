/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:25:26 by yim               #+#    #+#             */
/*   Updated: 2023/01/26 15:01:26 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //check
# include <unistd.h>
# include <string.h>
# include "libft/libft.h"

# define CODE_ERROR -1
# define CODE_OK 0
# define TRUE 1
# define FALSE 0

//builtins
void	cd(char *str, char **envp);
void	pwd(void);
#endif