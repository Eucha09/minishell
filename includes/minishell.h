/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:02:19 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/03 20:05:33 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "execute.h"
# include "builtins.h"

# define PROMPT			"minishell $ "
# define COLOR_BLUE		"\033[94;1m"
# define COLOR_CYAN		"\033[96;1m"
# define COLOR_RESET	"\033[0m"

void	print_minishell(void);
void	set_signal(int mode);

#endif