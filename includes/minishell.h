/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:02:19 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/17 12:56:48 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "command.h"
# include "lexer.h"
# include "parser.h"
# include "execute.h"
# include "builtins.h"
# include "error.h"
# include "sig.h"

# define PROMPT			"minishell-4.2$ "
# define COLOR_GREEN	"\033[32;1m"
# define COLOR_RESET	"\033[0m"

void	print_minishell(void);

#endif