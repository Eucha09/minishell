/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:03:39 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/14 17:00:14 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define TOKEN_WORD		0
# define TOKEN_PIPE		1
# define TOKEN_LESS		2
# define TOKEN_DLESS	3
# define TOKEN_GREAT	4
# define TOKEN_DGREAT	5

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token	*list_tok;
	int	tok_cnt;
}	t_lexer;

void	lexer_build(char *str, int size, t_lexer *lexer, char *envp[]);
void	lexer_clear(t_lexer *lexer);
void	strip_quotes(char *str);

int		gettok_pipe(char *str, t_lexer *lexer);
int		gettok_lesser(char *str, t_lexer *lexer);
int		gettok_greater(char *str, t_lexer *lexer);
int		gettok(char *str, int size, t_lexer *lexer, char *envp[]);

t_token	*toknew(int size);
void	tok_clear(t_token *tok);
void	lstadd_tok(t_lexer *lexer, t_token *tok);

void	expand_tok(t_token *tok, int size, char *envp[]);
int		expand_str(char **str, int size, char *envp[]);
int		replace_errno(char **str, int pos, int size);
void	divide_tok(t_token *tok, int size);
int		pos_to_divide(char *str);

int		replace_env(char **str, int pos, int size, char *envp[]);
char	env_key_len(char *key);
char	*get_env_value(char *key, int len, char *envp[]);

int		ft_isspace(char c);
int		isprs(char c);
int		isalnum_(char c);

#endif