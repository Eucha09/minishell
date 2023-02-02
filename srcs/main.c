/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:40:03 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/02 16:29:39 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void leaks()
{	
  system("leaks minishell");
}

void	sh_exit(int code)
{
	ft_printf("exit\n");
	exit(code);
}

int	main(int argc, char *argv[], char *envp[])
{
	atexit(&leaks);
	t_lexer	lexer;
	t_astnode* astree;
	char	*line;
	(void)argc;
	(void)argv;
	(void)envp;

	set_signal();
	ft_putstr_fd("hello minishell!\n", 1);
	while (1)
	{
		line = readline("minishell $ ");
		if (line == NULL)
			sh_exit(0);
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}
		add_history(line);
		lexer_build(line, ft_strlen(line), &lexer);
		free(line);

		// temp print lexer list
		ft_printf("lexer tok_cnt %d\n", lexer.tok_cnt);
		t_token *cur = lexer.list_tok;
		while(cur)
		{
			printf("token data %s type %d\n", cur->data, cur->type);
			cur = cur->next;
		}
		
		if (parse(&lexer, &astree)) {
			execute(astree, envp);
		}
		astnode_delete(astree);
		lexer_clear(&lexer);
	}
}