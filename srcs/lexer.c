/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:45:53 by jeong-euich       #+#    #+#             */
/*   Updated: 2023/02/12 22:13:41 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <stdio.h>

t_token	*toknew(int size)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (tok == NULL)
		return (NULL);
	tok->data = (char *)malloc(size + 1);
	if (tok->data == NULL)
	{
		free(tok);
		return (NULL);
	}
	ft_memset(tok->data, 0, size + 1);
	tok->type = TOKEN;
	tok->next = NULL;
	return (tok);
}

void	lstadd_tok(t_lexer *lexer, t_token *tok)
{
	t_token	*cur;

	if (lexer->list_tok == NULL)
	{
		lexer->list_tok = tok;
		return ;
	}
	cur = lexer->list_tok;
	while (cur && cur->next)
	{
		cur = cur->next;
	}
	cur->next = tok;
}

int	gettok_pipe(char *str, t_lexer *lexer)
{
	t_token	*tok;

	tok = toknew(1);
	if (tok == NULL)
		return (1);
	if (str[0] == '|')
		tok->data[0] = str[0];
	tok->type = TOKEN_PIPE;
	lstadd_tok(lexer, tok);
	return (1);
}

int	gettok_lesser(char *str, t_lexer *lexer)
{
	t_token	*tok;

	tok = toknew(2);
	if (tok == NULL)
		return (1);
	if (str[0] == '<')
	{
		tok->data[0] = str[0];
		tok->type = TOKEN_LESS;
	}
	if (str[1] == '<')
	{
		tok->data[1] = str[1];
		tok->type = TOKEN_DLESS;
	}
	lstadd_tok(lexer, tok);
	return (ft_strlen(tok->data));
}

int	gettok_greater(char *str, t_lexer *lexer)
{
	t_token	*tok;

	tok = toknew(2);
	if (tok == NULL)
		return (1);
	if (str[0] == '>')
	{
		tok->data[0] = str[0];
		tok->type = TOKEN_GREAT;
	}
	if (str[1] == '>')
	{
		tok->data[1] = str[1];
		tok->type = TOKEN_DGREAT;
	}
	lstadd_tok(lexer, tok);
	return (ft_strlen(tok->data));
}

// char	envp_key_len(char *key)
// {
// 	int	len;

// 	len = 0;
// 	if (ft_isdigit(key[0]))
// 		return (1);
// 	while (ft_isalnum(key[len]) || key[len] == '_')
// 		len++;
// 	return (len);
// }

// char	*get_envp_value(char *key, int len, char *envp[])
// {
// 	int		i;
// 	char	temp;

// 	temp = key[len];
// 	key[len++] = '=';
// 	i = 0;
// 	while(envp[i])
// 	{
// 		if (ft_strncmp(key, envp[i], len) == 0)
// 		{
// 			key[len - 1] = temp;
// 			return (envp[i] + len);
// 		}
// 		i++;
// 	}
// 	key[len - 1] = temp;
// 	return (NULL);
// }

// int	replace_envp_total_size(char *str, int size, char *envp[])
// {
// 	int		i;
// 	int		key_len;
// 	char	quote;
// 	char	*envp_value;

// 	i = 0;
// 	quote = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
// 			quote = str[i];
// 		else if (str[i] == quote)
// 			quote = 0;
// 		else if (str[i] == '$' && (ft_isalnum(str[i + 1] || str[i] == '_')) && quote != '\'')
// 		{
// 			key_len = envp_key_len(str + i + 1);
// 			envp_value = get_envp_value(str + i + 1, key_len, envp);
// 			if (envp_value != NULL)
// 				size += ft_strlen(envp_value);
// 			i += key_len + 1;
// 		}
// 		i++;
// 	}
// 	return (size);
// }

// void	insert_envp_value(char *str, int size, char *envp[])
// {
	
// }

// char	*replace_envp(char *str, int size, char *envp[])
// {
// 	int		i;
// 	int		key_len;
// 	char	quote;
// 	char	*envp_value;
// 	char	*new_str;
	
// 	size = replace_envp_total_size(str, size, envp);
// 	new_str = (char *)ft_calloc(sizeof(char), size + 1);
// 	ft_strlcpy(new_str, str, size + 1);
// 	i = 0;
// 	quote = 0;
// 	while (new_str[i])
// 	{
// 		if ((new_str[i] == '\'' || new_str[i] == '\"') && quote == 0)
// 			quote = str[i];
// 		else if (new_str[i] == quote)
// 			quote = 0;
// 		else if (new_str[i] == '$' && (ft_isalnum(new_str[i + 1] || new_str[i] == '_')) && quote != '\'')
// 		{
// 			key_len = envp_key_len(new_str + i + 1);
// 			envp_value = get_envp_value(new_str + i + 1, key_len, envp);
// 			if (envp_value != NULL)
// 			{
// 				ft_memmove(new_str + i + ft_strlen(envp_value), new_str + i, )
// 			}
// 			i += key_len + 1;


// 			envp_value = get_envp_value(str + i + 1, envp);
// 			size += ft_strlen(envp_value);
// 			temp = new_str;
// 			new_str = (char *)ft_calloc(sizeof(char), size + 1);
// 			ft_strlcat(new_str, temp, size + 1);
// 			ft_strlcat(new_str, envp_value, size + 1);
// 			free(temp);
// 		}
// 		else

// 		i++;
// 	}
// }

int	isalnum_(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	env_key_len(char *key)
{
	int	len;

	len = 0;
	if (ft_isdigit(key[0]))
		return (1);
	while (isalnum_(key[len]))
		len++;
	return (len);
}

char	*get_env_value(char *key, int len, char *envp[])
{
	int		i;
	char	temp;

	temp = key[len];
	key[len] = '=';
	i = 0;
	while(envp[i])
	{
		if (ft_strncmp(key, envp[i], len + 1) == 0)
		{
			key[len] = temp;
			return (envp[i] + len + 1);
		}
		i++;
	}
	key[len] = temp;
	return ("");
}

int	replace_env(char **str, int pos, int size, char *envp[])
{
	char	*new_str;
	char	*env_value;
	int		key_len;
	int		value_len;
	int		new_size;

	//printf("replace env str %s, pos %d\n", *str, pos);
	key_len = env_key_len(*str + pos + 1);
	env_value = get_env_value(*str + pos + 1, key_len, envp);
	value_len = ft_strlen(env_value);
	new_size = size + value_len + 1;
	new_str = (char *)malloc(sizeof(char) * new_size);
	if (new_str == NULL)
		return (0); // todo
	// ft_strlcpy(new_str, (*str), pos + 1);
	// ft_strlcpy(new_str + pos, env_value, value_len + 1);
	// ft_strlcpy(new_str + pos + value_len, (*str) + pos + 1 + key_len, str_len - pos - key_len);

	ft_strlcpy(new_str, (*str), pos + 1);
	ft_strlcat(new_str, env_value, new_size);
	ft_strlcat(new_str, (*str) + pos + 1 + key_len, new_size);
	free(*str);
	*str = new_str;
	//printf("ret replace %s\n", *str);
	return (value_len);
}

int	expand_str(char **str, int size, char *envp[])
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while ((*str)[i])
	{
		if (((*str)[i] == '\'' || (*str)[i] == '\"') && quote == 0)
			quote = (*str)[i];
		else if ((*str)[i] == quote)
			quote = 0;
		if ((*str)[i] == '$' && isalnum_((*str)[i + 1]) && quote != '\'')
			i += replace_env(str, i, size, envp);
		else
			i++;
	}
	//printf("end expand_str\n");
	return (i);
}

int	pos_to_divide(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] && (str[i] != ' ' || quote != 0))
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		i++;
	}
	while (str[i] == ' ')
		i++;
	//printf("i %d\n", i);
	return (i);
}

void	divide_tok(t_token *tok, int size)
{
	t_token	*new_tok;
	int i;

	i = pos_to_divide(tok->data);
	//printf("pos to divide i %d\n", i);
	if (i < size)
	{
		new_tok = toknew(size - i);
		ft_strlcpy(new_tok->data, tok->data + i, size - i + 1);
		tok->data[i] = '\0';
		tok->next = new_tok;
		divide_tok(new_tok, size - i);
	}
}

void	expand_tok(t_token *tok, int size, char *envp[])
{
	size = expand_str(&(tok->data), size, envp);
	//printf("new str %s\n", tok->data);
	divide_tok(tok, size);
}

int	gettok(char *str, int size, t_lexer *lexer, char *envp[])
{
	t_token	*tok;
	int		i;
	char	quote;
	int		expand;

	tok = toknew(size);
	if (tok == NULL)
		return (1);
	i = 0;
	quote = 0;
	expand = 0;
	while (str[i] && (str[i] != ' ' || quote != 0))
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		if (str[i] == '$' && isalnum_(str[i + 1]) && quote != '\'')
			expand = 1;
		tok->data[i] = str[i];
		i++;
	}
	if (expand)
		expand_tok(tok, i, envp);
	lstadd_tok(lexer, tok);
	return (i);
}

void	strip_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] && (str[i] != ' ' || quote != 0))
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (str[i])
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

void	lexer_build(char *str, int size, t_lexer *lexer, char *envp[])
{
	t_token	*cur;
	int	i;

	lexer->list_tok = NULL;
	lexer->tok_cnt = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '|')
			i += gettok_pipe(str + i, lexer);
		else if (str[i] == '<')
			i += gettok_lesser(str + i, lexer);
		else if (str[i] == '>')
			i += gettok_greater(str + i, lexer);
		else if (str[i])
		{
			i += gettok(str + i, size - i, lexer, envp);
			lexer->tok_cnt++;
		}
	}
	cur = lexer->list_tok;
	while (cur)
	{
		strip_quotes(cur->data);
		cur = cur->next;
	}
}

void	tok_clear(t_token *tok) {
	if (tok == NULL)
		return ;
	free(tok->data);
	tok_clear(tok->next);
	free(tok);
}

void	lexer_clear(t_lexer *lexer)
{
	if (lexer == NULL)
		return;
	tok_clear(lexer->list_tok);
}
