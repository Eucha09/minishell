/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:40:03 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/13 14:53:31 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void leaks()
// {	
//   system("leaks minishell");
// }

void	sh_exit(int code)
{
	ft_printf("exit\n");
	exit(code);
}

char	**dup_envp(char *envp[])
{
	int		i;
	char	**d_envp;

	i = 0;
	d_envp = (char **)malloc(sizeof(char *) * 250);
	if (d_envp == NULL)
		return (NULL);
	while (envp[i])
	{
		d_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	d_envp[i] = NULL;
	return (d_envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	//atexit(&leaks);
	t_lexer	lexer;
	t_astnode* astree;
	char	*line;
	char	**d_envp;
	(void)argc;
	(void)argv;

	//나중에 free, return을 해야하나?
	d_envp = dup_envp(envp);
	if (d_envp == NULL)
		return (0);
	set_signal(0);
	print_minishell();
	while (1)
	{
		line = readline(COLOR_GREEN PROMPT COLOR_RESET);
		if (line == NULL)
			sh_exit(0);
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}
		add_history(line);
		lexer_build(line, ft_strlen(line), &lexer, d_envp);
		free(line);

		// temp print lexer list
		// printf("lexer tok_cnt %d\n", lexer.tok_cnt);
		// t_token *cur = lexer.list_tok;
		// while(cur)
		// {
		// 	printf("token data %s type %d\n", cur->data, cur->type);
		// 	cur = cur->next;
		// }
		
		if (parse(&lexer, &astree)) {
			execute(astree, d_envp);
		}
		astnode_delete(astree);
		lexer_clear(&lexer);
	}
}