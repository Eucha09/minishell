/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:02:19 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/14 16:07:39 by eujeong          ###   ########.fr       */
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
# include "command.h"
# include "lexer.h"
# include "parser.h"
# include "execute.h"
# include "builtins.h"

# define SIG_SHELL_MODE		0
# define SIG_EXECVE_MODE	1
# define SIG_CHILD_MODE		2
# define SIG_HEREDOC_MODE	3

# define PROMPT			"minishell $ "
# define COLOR_GREEN	"\033[32;1m"
# define COLOR_RESET	"\033[0m"

void	print_minishell(void);
void	set_signal(int mode);

#endif